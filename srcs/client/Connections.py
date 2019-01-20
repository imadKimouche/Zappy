#!/usr/bin/python2.7

from __future__ import print_function
import socket
import errno

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
instructions = 1
broadcast = []
stop = False
cmd_incoming = []
#buff_data = []
#buff_write = 0
#buff_read = 0
#buff_size = 1000

#def b_add(content):
#    for letter in content:
#        buff_data.insert(buff_write % buff_size, letter)
#        buff_write += 1

#def b_get_instruction():
#    global buff_read

#    res = ""
#    for i in range(buff_read, buff_write):
#        res += buff_data[i % buff_size]
#        if buff_data[i % buff_size] == '\n':
#            buff_read = i + 1
#            return res
#    return None
        
def connect(host, port):
    global server
    global instructions
    try:
        server.connect((host, port))
    except socket.error, exc:
        print("No avaiable server found")
        exit(1)
    server.setblocking(0)
    res = None
    while res == None:
        res = receive()

def disconnect():
    global server
    global instructions
    server.close()

def send(msg):
    global server
    global instructions
    if stop or len(msg) == 0:
        return None
    if instructions + msg.count("\n") > 9:
        one_by_one(msg)
    else:
        instructions += msg.count("\n")
        server.send(msg)
        print("I:", instructions,end="")
        print("Sending:",end="")
        print(msg,end="")

def one_by_one(msg):
    res = receive_wait()
    msg = msg.split("\n")
    msg.pop(len(msg) - 1)
    for cmd in msg:
        send(cmd + "\n")
        tmp_res = receive_wait()
        if tmp_res != None:
            res += tmp_res

def inspect_resp(resp):
    global broadcast
    global instructions
    global cmd_incoming
    res = []
    for cmd in resp:
        if cmd == "dead":
            print("ERGHWHEHHH")
            print("NB INSTRUCTIONS :", instructions)
            exit()
        elif cmd.count("message") > 0:
            msg = cmd.split(" ")
            msg.pop(0)
            msg[0] = msg[0].replace(",", "")
            broadcast.insert(len(broadcast), msg)
        elif "Current level:" in cmd:
            print("level up from Connexions")
            res.insert(len(res), cmd)
        elif "Elevation:" in cmd:
            print("elevation")
        elif "Eject" in cmd :
            cmd_incoming.insert(len(cmd_incoming), cmd)
        else:
            res.insert(len(res), cmd)
    instructions -= len(res)
    return res

def receive():
    global server
    global instructions
    if stop:
        return None
    try:
        resp = server.recv(99999)
    except socket.error, e:
        if e.args[0] == errno.EAGAIN or e.args[0] == errno.EWOULDBLOCK:
            return None
        else:
            print("Socket closed")
            exit(1)
    if resp == None or len(resp) == 0:
        return None
    if resp[len(resp) - 1] != '\n':
        server.setblocking(1)
        resp += server.recv(99999)
        server.setblocking(0)
    resp = resp.split("\n")
    resp.pop(len(resp) - 1)
    resp = inspect_resp(resp)
    if instructions < 0:
        instructions = 0
    if len(resp) != 0:
        print("I: ",end="")
        print(instructions,end="")
        print(" Receive:",end="")
        print(resp)
        return resp
    return None

def receive_wait():
    cmd = receive()
    server.setblocking(1)
    while cmd == None or instructions > 0:
        if stop:
            return None
        cmd = receive()
    server.setblocking(0)
    return cmd

def getBroadcast():
    return broadcast

def getIncomingCommands():
    global cmd_incoming
    tmp = cmd_incoming
    cmd_incoming = []
    return tmp

def sendBroadCast(level, message):
    msg = "Broadcast "
    msg += str(level)
    msg += " "
    msg += message
    msg += "\n"
    print("Sending Broadcast : " + msg)
    send(msg)
