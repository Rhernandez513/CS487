# HMWK3 Buffer Overflow Attack Lab (Set-UID Version)

CS487 Secure Computer Systems

Robert D. Hernandez <rherna70@uic.edu>

## Env Setup 

See the included taskfile for linking sh to zsh and disabling ASLR convenience scripts `task disable_alr`, `link_to_zsh`

## Task 1: 

I tried compiling shellcode/32_bit_shellcode.s and shellcode/64_bit_shellcode.s with gcc but was met with:

```➜  shellcode git:(hw3/buffer_overflow_attack_lab) ✗ gcc -m32 -DBUF_SIZE=100 fno-stack-protector -z noexecstack -o 32 32_bit_shellcode.s 
32_bit_shellcode.s: Assembler messages:
32_bit_shellcode.s: Warning: end of file not at end of a line; newline inserted
32_bit_shellcode.s:1: Error: no such instruction: `store the command on stack'
32_bit_shellcode.s:2: Error: too many memory references for `xor'
32_bit_shellcode.s:6: Error: too many memory references for `mov'
32_bit_shellcode.s:6: Error: no such instruction: `ebx -->"/bin//sh":execve()’s 1st argument'
32_bit_shellcode.s:7: Error: no such instruction: `construct the argument array argv[]'
32_bit_shellcode.s:8: Error: invalid character '[' in mnemonic
32_bit_shellcode.s:9: Error: invalid character '[' in mnemonic
32_bit_shellcode.s:10: Error: too many memory references for `mov'
32_bit_shellcode.s:10: Error: no such instruction: `ecx -->argv[]:execve()’s 2nd argument'
32_bit_shellcode.s:11: Error: no such instruction: `for environment variable'
32_bit_shellcode.s:12: Error: too many memory references for `xor'
32_bit_shellcode.s:12: Error: junk at end of line, first unrecognized character is `:'
32_bit_shellcode.s:13: Error: no such instruction: `invoke execve()'
32_bit_shellcode.s:14: Error: too many memory references for `xor'
32_bit_shellcode.s:15: Error: too many memory references for `mov'
32_bit_shellcode.s:15: Error: invalid character '(' in mnemonic
32_bit_shellcode.s:16: Error: operand size mismatch for `int'
```

## Task 2: 

I created a simple taskfile entry to build and clean `stack.c` `call.shellcode.c` `shellcode.c`

![alt text](images/build.png)

## Task 3: Launching Attack on 32-bit Program (Level 1)

We begin by running the compiled `stack.c` with `gdb` and we set a breakpoint at the `bof()` function, we see pwndbg below:

![alt text](images/stack_bof_break.png)

I didn't have `$ebp` on my machine I had `$rbp` so printing that value we see the value of `$rbp` is `0x7fffffffdce0`

![alt text](images/rbp_print.png)

and the address of `&buffer` is `0x7ffff7fb0e30`

![alt text](images/buffer_address.png)

