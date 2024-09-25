/* Copyright © 2024 cpmachado */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

int main() {
  /*
   * Permission groups: 0 USER GROUP OTHER
   * Permissions: R: 4    W: 2   X: 1
   */
  /* don't make it executable for christ sake*/
  int file = open("newFile.txt", O_RDWR | O_CREAT, 0640);

  if (file < 0 || close(file) < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
