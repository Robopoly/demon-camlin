#!/usr/bin/env python

import serial

import gobject
import matplotlib
matplotlib.use('GTKAgg')

from matplotlib import pyplot as plt
import numpy as np

from pylab import *



port = '/dev/ttyUSB1'

s = serial.Serial(port, 9600, timeout=0, parity=serial.PARITY_NONE)

f = plt.figure(1, figsize=(18,11))

#while True:
#    c = s.read()
#    if(len(c) > 0):
#        print(ord(c))

# read chars in loop
def update(vars):
# wait for start
    c = '0'
    while(c != 'S'):
        c = s.read()
    print(c)

    # T
    while(c != 'T'):
        c = s.read()
    print(c)

    # A
    while(c != 'A'):
        c = s.read()
    print(c)

    # R
    while(c != 'R'):
        c = s.read()
    print(c)

    # T
    while(c != 'T'):
        c = s.read()
    print(c)


# add 102 chars to array
    ar = []
    while (len(ar) < 102):
        c = s.read()
        if len(c) > 0:
            ar.append(ord(c)-ord('0'))
    print(ar)

    f.clear()
    f.suptitle("Linear Camera Data")
    a = f.add_subplot(111)
    a.bar(arange(len(ar)), ar)

    a.axis([0,102,0,33])

    plt.xlabel("Pixels")
    plt.ylabel("Intensity")
    f.canvas.draw()

    return True



gobject.timeout_add(500, update, vars)

plt.show()

while True:
    x = 1

s.close()
