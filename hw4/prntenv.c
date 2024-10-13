#include <stdio.h>
#include <stdlib.h>

void main() {
	char* shell = getenv("MYSHELL");
	if (shell) {
		printf("%x\n", (unsigned int)shell);
	}
	char* args = getenv("MYARGS");
	if (args) {
		printf("%x\n", (unsigned int)args);
	}
}

