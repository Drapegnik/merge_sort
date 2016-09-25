#!/usr/bin/python

import sys
import random

f = open('input.txt', 'w')
f.write(sys.argv[1] + '\n')
for i in range(int(sys.argv[1])):
    f.write(str(random.randint(0, int(sys.argv[2]))) + ' ')

f.close()
