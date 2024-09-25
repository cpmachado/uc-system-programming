/* Copyright © 2024 cpmachado */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char *str = "hello, world\n";
  printf("%s", str);
  /* with write syscall */
  write(STDOUT_FILENO, str, strlen(str));

  return 0;
}
