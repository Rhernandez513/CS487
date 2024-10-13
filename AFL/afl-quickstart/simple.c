#include <stddef.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char data[100] = {0};
  size_t size = read(0, data, 100);

  if (size > 0 && data[0] == '4')
    if (size > 1 && data[1] == '8')
      if (size > 2 && data[2] == '7')
        __builtin_trap();

  return 0;
}

