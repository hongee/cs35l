#!/usr/bin/python
import random
import string

s = ''.join(random.choice(string.ascii_letters + ' ') for _ in range(500000))
print s
