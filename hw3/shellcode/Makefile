TARGET = shellcode

all: ${TARGET}

N = 100
shellcode: call.shellcode.c shellcode.c
	gcc -m32 -DBUF_SIZE=${N} -fno-stack-protector -z noexecstack -o $@ $@.c
	sudo chown root $@ && sudo chmod 4755 $@

clean:
	rm -f *.o *.out ${TARGET} badfile
