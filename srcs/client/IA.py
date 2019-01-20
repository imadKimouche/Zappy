#!/usr/bin/python2.7

import Client
import Connections
from enum import Enum
from itertools import imap

class StateType(Enum):
	searchMinerals = 0
	findTeam = 1
	incantate = 2

class BroadcastMessageType(Enum):
	none = 0
	searchingSameLevel = 1
	respondingFromSameLevel = 2
	waitingForLvlUp = 3

class IA:

##		INIT
	def __init__(self, client):
		_client = client


##		MAIN LOOP
	def start(self):
		while self._client._dead == False:
			print
			print("Player is", self._client.lvl, " -----------")
			print
                        self._client.exec_incoming_cmd()
                        if self._client._reproduced == False:
                                self._client.lay_egg()
                        self._client.update()
                        print("updated")
			if int(self._client._food) < 4:
				self.findFood()
			if self.checkBroadCastMessage() == False:
                                self._actions[self._state](self)
			while len(Connections.broadcast) > 0 : Connections.broadcast.pop()

##		SEARCH MINERALS

	rotateTime = 0
	def move(self):
		print("Moving")
		if int(self.rotateTime) == 3:
			self.rotateTime = 0
			Connections.send("Left\n")
			Connections.send("Forward\n")
			Connections.send("Forward\n")
			Connections.send("Forward\n")
			Connections.send("Forward\n")
		else:
			self.rotateTime += 1
			Connections.send("Left\n")

	def searchMinerals(self):
		print("SearchMinerals action")
		found = False
		if self.checkMinerals() == True:
			self._state = StateType.incantate
			print("checkminerals ok")
			return
		for mineral, value in sorted(self._client._stone.iteritems(), key=lambda x:x[0].lower, reverse=True):
			if int(value) < int(self._client._incantationLevel[mineral]):
				print("Searching for " + mineral)
				if self._client.search(mineral) != None:
					print(mineral + " found")
					Connections.send("Take " + mineral + "\n")
					self.rotateTime = 0
					found = True
					break
		if found == False:
			self.move()
			return


##		FIND TEAM
	def findTeam(self):
		self._state = StateType.searchMinerals


##		INCANTATE
	def sameLevelMessage(self, msg, tile):
		print("Message From Same level")
		if self._broadcastState == BroadcastMessageType.none:
			if msg == "needPlayers":
				print("Have to go to", tile)
				if tile == 0:
					self._broadcastState = BroadcastMessageType.waitingForLvlUp
				else:
					self._client.goToTile(tile)
	waitingTime = 0

	def checkBroadCastMessage(self):
		for message in Connections.getBroadcast():
			if int(message[0]) == 0 and int(message[1]) == int(self._client.lvl):
				print("SAMETILE")
				print("SAMETILE")
				print("SAMETILE")
				print("SAMETILE")
				if "willIncantate" in message[2]:
					print(Connections.receive())
				if "Incantation Failed" in message[2]:
                                        print("Incantation failed")
					self._broadcastState = BroadcastMessageType.none
				return True
		for message in Connections.getBroadcast():
			if int(message[1]) == int(self._client.lvl):
				self.sameLevelMessage(message[2], int(message[0]))
				return True
		return False


	def getNbPlayersOnCase(self):
		return int(self._client._map[0][1].count("player"))

	def searchOthersPlayers(self):
		level = self._client.lvl
		Connections.sendBroadCast(level, "needPlayers")

	def checkEmptyTile(self):
		if any(imap(self._client._map[0][1].__contains__, self._client.minerals)) == True:
			i = 0
			for tile in self._client._map:
				if any(imap(tile[1].__contains__, self._client.minerals)) == False:
					self._client.go(self._client.vision_move[int(i)])
					return False
				i += 1
			self.move()
			return False
		else:
			return True

	def checkConditions(self):
		if self.checkMinerals() == False:
			self._state = StateType.searchMinerals
			return False
		if self.checkEmptyTile() == False:
			return False
		if int(self.getNbPlayersOnCase()) != int(self._client._incantationLevel["players"]):
			print("Missing Players")
			self.searchOthersPlayers()
			return False
		if int(self._client._food) < 4:
			print("Player will die, search food")
			self.findFood()
			return False

	def setMinerals(self):
		for mineral, value in self._client._stone.iteritems():
			i = 0
			while i < int(value):
				Connections.send("Set " + mineral + "\n")
				i += 1

	def incantate(self):
		print("Incantate Function")
		if self.checkConditions() == False:
			return
		print("Incantation possible, start")
		self.setMinerals()
		Connections.sendBroadCast(self._client.lvl, "willIncantate")
		Connections.send("Incantation\n")
		response = Connections.receive_wait()
		if response[len(response) - 1] == "ko":
			print("Incantation failed")
			response = Connections.receive()
			Connections.sendBroadCast(self._client.lvl, "Incantation Failed")
			print("Response : ", response)
			self._client.update()
			print("Map : ", self._client._map)
			print("Inventory : ", self._client._stone)
		elif response[len(response) - 1] == "Elevation underway":
			print("Waiting for elevation response")
			response = Connections.receive_wait()
			if "Current level:" in str(response[len(response) - 1]):
				self._client.lvlup()
				self._state = StateType.findTeam
				print("Yata !!! level up")
				print(response[len(response) - 1])
			else:
				print("Elevation failed")
				print(response)

	def checkMinerals(self):
		for mineral, value in self._client._stone.iteritems():
			if int(value) < int(self._client._incantationLevel[mineral]):
				print("Missing stones")
				return False
		return True


##		FIND FOOD
	def findFood(self):
		if self._client.search("food") != None:
                        Connections.send("Take " + "food" + "\n")
		if self._client.search("food") != None:
                        Connections.send("Take " + "food" + "\n")
		if self._client.search("food") != None:
                        Connections.send("Take " + "food" + "\n")
                print("Eating")

##		ATTRIBUTES
	_broadcastState = BroadcastMessageType.none
	_state = StateType.findTeam
        _client = Client.Client()
        _actions = {
	        StateType.searchMinerals : searchMinerals,
	        StateType.findTeam : findTeam,
	        StateType.incantate : incantate
	}
