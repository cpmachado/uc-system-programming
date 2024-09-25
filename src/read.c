/* Copyright © 2024 cpmachado */
/*
 * I added the cli argument as to simplify the repository
 **/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

int main(int argc, char *argv[]) {
  int fd;
  char buffer[100];
  int n;

  if (argc != 2) {
    printf("Need file to read\nUsage: %s <file>\n", *argv);
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDONLY, 0777);
  if (fd < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  while ((n = read(fd, buffer, 100)) > 0) {
    printf("%.*s\n", n, buffer);
  }

  if (close(fd) < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
