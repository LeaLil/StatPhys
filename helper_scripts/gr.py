#!/usr/bin/python

import re,string
import sys

f = open(sys.argv[1],"r")

pattern1 = re.compile("Radial distribution function")
pattern2 = re.compile("Timing:")
pattern3 = re.compile(" +[0-9Ee\+-\.]+ +[0-9Ee\+-\.]+")

while 1:
    line = f.readline()
    if not line:
        raise EOFError
    if pattern1.search(line) != None:
        break
    
while 1:
    line = f.readline()
    if not line:
        raise EOFError
    if pattern3.search(line) != None:
        print(line[:-1])
        #t = string.split(line)
    if pattern2.search(line) != None:
        break


