#!/usr/bin/env python

import serial

port = '/dev/ttyUSB1'

s = serial.Serial(port, 9600, timeout=0, parity=serial.PARITY_NONE)

# read chars in loop
while True:
# wait for start
    c = '0'
    while(c != 'S'):
        c = s.read()

    # T
    while(c != 'T'):
        c = s.read()

    # A
    while(c != 'A'):
        c = s.read()

    # R
    while(c != 'R'):
        c = s.read()

    # T
    while(c != 'T'):
        c = s.read()


# add 102 chars to array
ar = []
    while (len(ar < 103)):
        c = s.read()
        if len(c) > 0:
            ar = ar


        

s.close()
