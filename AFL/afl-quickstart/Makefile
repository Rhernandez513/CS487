# Enable debugging and suppress pesky warnings
CFLAGS ?= -g -w

all:	vulnerable simple

clean:
	rm -f vulnerable simple

vulnerable: vulnerable.c
	${CC} ${CFLAGS} $< -o $@

simple: simple.c
	${CC} ${CFLAGS} $< -o $@
