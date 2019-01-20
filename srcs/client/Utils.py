#!/usr/bin/python2.7

def sanitizeList(msg):
    res = msg[0]
    res = res.replace("[ ", "")
    res = res.replace(" ]", "")
    res = res.replace(", ", ",")
    res = res.replace("\n", "")
    res = res.split(",")
    return res

def sanitizeStringToList(msg):
    res = msg
    res = res.replace("[ ", "")
    res = res.replace(" ]", "")
    res = res.replace(", ", ",")
    res = res.replace("\n", "")
    res = res.split(",")
    return res
