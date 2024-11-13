#include <stdio.h>

/* Return the absolute value of I. */
int absolute(int i) {
    if (i < 0) {
        return -i;
    } else {
        return i;
    }
}

void pw() {
    int passwd;
    printf("Password: ");
    scanf("%d", &passwd);
    if (absolute(passwd) < 0) {
        printf("Password OK :)\n)");
    } else {
        printf("Invalid Password!\n");
    }
}

int main(int argc, char *argv[])
{
    pw();
    return 0;
}
