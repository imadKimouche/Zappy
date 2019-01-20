#!/usr/bin/python2.7

from __future__ import print_function
import operator
import time
import Connections
import Utils

class Client:

    def __init__(self):
        self._incantationLevel = {"players":0, "linemate":0, "deraumere":0,
                                  "sibur":0, "mendiane":0, "phiras":0, "thystame":0}
        self.lvl = 0
        self.mapLookSize = 4
        self._team = -1
        self.lvlup()
        self._map_size = [0, 0]
        self._stone = {}
        self._food = 0
        self._dead = False
        self._place = 0
        self._reproduced = False

##       Initialise Connection and starting attributes
    def init(self, team, host, port):
        Connections.connect(host, port)
        self._team = team
        Connections.send(team + "\n")
        rep = None
        rep = Connections.receive_wait()
        if rep[0] == "ko":
            print("No more place on the server or wrong team name")
            exit(0)
        self._place = rep[0]
        if len(rep) <= 1:
            rep = Connections.receive_wait()
            rep = rep[0]
        else:
            rep = rep[1]
        map_size = rep.split(" ")
        self._map_size[0] = map_size[0]
        self._map_size[1] = map_size[1]

##       Level up the player
    def lvlup(self):
        self.lvl += 1
        self._incantationLevel["players"] = Client.levels[self.lvl][0]
        self._incantationLevel["linemate"] = Client.levels[self.lvl][1]
        self._incantationLevel["deraumere"] = Client.levels[self.lvl][2]
        self._incantationLevel["sibur"] = Client.levels[self.lvl][3]
        self._incantationLevel["mendiane"] = Client.levels[self.lvl][4]
        self._incantationLevel["phiras"] = Client.levels[self.lvl][5]
        self._incantationLevel["thystame"] = Client.levels[self.lvl][6]

##       Check if the received cmd is the Look responce
    def checkMapResponse(self, msg):
        if len(msg) != int(self.lvl + 1)**2:
            print("Map parsing error : Map = ", end="")
            print(msg)
            print(int(self.lvl + 1)**2)
            print(self.lvl)
            return False
        else:
            print(msg)
        return True

##       Check if the received cmd is the Inventory responce
    def checkInventory(self, msg):
        if len(msg) != 7:
            print("ERROR ON PARSING INVENTORY")
            print(msg)
            return False
        else:
            print(msg)
        return True
        
##       Update the player's map
    def update_map(self):
        Connections.receive()
        cmd = None
        while cmd == None or self.checkMapResponse(cmd) == False:
            Connections.send("Look\n")
            resp = Connections.receive_wait()
            resp = resp[len(resp) - 1]
            if resp == "ko":
                return
            cmd = Utils.sanitizeStringToList(resp)
        full_map = [None] * len(cmd)
        for index,tile in enumerate(cmd):
            full_map[index] = [len(self.vision_move[index]), tile, self.vision_move[index]]
        self._map = sorted(full_map, key=operator.itemgetter(0))

##       Update the player's Inventory
    def update_inventory(self):
        Connections.receive()
        resp = None
        while resp == None or self.checkInventory(cmd) == False:
            Connections.send("Inventory\n")
            resp = Connections.receive_wait()
            if resp == None:
                self.dead()
                return None
            resp = resp[len(resp) - 1]
            if resp == "ko":
                return
            cmd = Utils.sanitizeStringToList(resp)
        try:
            self._food = int(cmd[0].split(" ")[1])
        except:
            print("segfault when update food:")
            print(cmd, resp)
            exit(1)
        cmd.pop(0)
        for item in cmd:
            try:
                split = item.split(" ")
            except ValueError:
                print("segfault when update stones:")
                print(item)
                print(resp)
                print(cmd)
                exit(1)
            self._stone[split[0]] = split[1]

##       Update the number of new player avaiable
    def update_place(self):
        Connections.receive()
        stop = False
        while stop != True :
            Connections.send("Connect_nbr\n")
            resp = Connections.receive_wait()
            if resp == None:
                self.dead()
                return None
            resp = resp[len(resp) - 1]
            if resp == "ko":
                    return None
            try:
                self._place = int(resp)
                stop = True
            except ValueError:
                stop = False
        
##       Kill the player
    def dead(self):
        self._dead = True
        print("I'm dead now, why did you do this ?")

##       Return receitioned broadcast
    def get_broadcast(self):
        return Connections.getBroadcast()

##       Excecute incoming commands
    def exec_incoming_cmd(self):
        cmds = Connections.getIncomingCommands()
        for cmd in cmds:
            if "Current level:" in cmd:
                self.lvlup()
            if "Eject" in cmd:
                cmd = cmd.split(" ")
                if len(cmd) == 2:
                    self.go(Client.directions[1])
            elif "Elevation underway" in cmd:
                pass

##        Ask to update map and inventory
    def update(self):
        self.update_map()
        self.update_inventory()
        self.update_place()

##        Search an element in the map
    def find(self, f_map, elem):
        for tile in f_map:
            if tile[1].find(elem) != -1:
                return tile[2]
        return None

##        Move to the given tile
    def goToTile(self, tile):
        cmd = ""
        path = self.tile_move[int(tile)]
        for letter in path:
            cmd += self.vision_move_translate[letter]
        Connections.send(cmd)

##        Follow the path given
    def go(self, path):
        cmd = ""
        for letter in path:
            cmd += self.vision_move_translate[letter]
        Connections.send(cmd)

##        Search a given element and if found move to the tile
    def search(self, elem):
        path = self.find(self._map, elem)
        if (path == None):
            return None
        self.go(path)
        return 1

    def lay_egg(self):
        if self._food == 9 or self._place <= 0:
            return None
        print("Laying an eggs")
        Connections.receive()
        Connections.send("Fork\n")
        Connections.receive_wait()
        print("Finishing Laying")
        self._reproduced = True
    def __del__(self):
        Connections.disconnect()

##        STATIC ATTRIBUTES    
    minerals = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
    levels = [[0,0,0,0,0,0,0], [1,1,0,0,0,0,0], [2,1,1,1,0,0,0], [2,2,0,1,0,2,0], [4,1,1,2,0,1,0],
              [4,1,2,1,3,0,0], [6,1,2,3,0,1,0], [6,2,2,2,2,2,1]]
    vision_move = ["", "flf", "f", "frf", "fflff", "fflf", "ff",
                   "ffrf", "ffrff", "ffflfff", "ffflff", "ffflf",
                   "fff", "fffrf", "fffrff", "fffrfff"]
    vision_move_translate = {"f":"Forward\n", "l":"Left\n", "r":"Right\n"}
    tile_move = ["", "f", "f", "lf", "lf", "llf", "rrf", "rf", "f"]
    directions = {"1":"f", "3":"lf", "5":"llf", "7":"rf"}
    rotate_time = 0
    receiv_to_destroy = 0
