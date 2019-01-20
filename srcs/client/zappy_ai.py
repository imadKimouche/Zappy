#!/usr/bin/python2.7

import Client
import IA
import sys

param = {"port":0, "team":"", "host":""}

def display_help():
    print "USAGE: ./zappy_ai -p port -n name -h machine"
    print "\tport\tis the port number"
    print "\tname\tis the name of the team"
    print "\tmachine\tis the name of the machine; localhost by default"

def parse_args(args):
    cmd = ""
    if len(args) > 0:
        args.pop(0)
    if len(args) == 0:
        return False
    for word in args:
        if len(word) == 0:
            print("Spoil: A c'est Alison")
            return False
        if word[0] == '-':
            if len(word) != 2:
                return False
            if word[1] == 'p':
                cmd = "port"
            elif word[1] == 'n':
                cmd = "team"
            elif word[1] == 'h':
                cmd = "host"
            else:
                return False
        else:
            if cmd in param.keys():
                if cmd == "port":
                    word = int(word)
                param[cmd] = word
            else:
                return False
    return True

def check_validity():
    if param["port"] <= 1024 or param["port"] >= 65000:
        print "Invalid port, type ./zappy_ai -help for help"
    elif param["team"] == "":
        print "Team name needed, type ./zappy_ai -help for help"
    else:
        return True
    return False

def my_main():
    if parse_args(sys.argv) == False:
        display_help()
        sys.exit()
    if check_validity() == False:
        sys.exit()
    client = Client.Client()
    client.init(param["team"], param["host"], param["port"])
    ia = IA.IA(client)
    ia.start()

if __name__ == '__main__':
    my_main()
