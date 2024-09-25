/* Copyright © 2024 cpmachado */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

int main(int argc, char *argv[]) {
  const char *output_file = "modified_text.txt";
  int fd, fd2, n, n_reads = 0;
  char buffer[100];

  if (argc != 2) {
    printf("Need file to read\nUsage: %s <file>\n", *argv);
    exit(EXIT_FAILURE);
  }

  if ((fd = open(argv[1], O_RDWR | O_CREAT, 0666)) < 0 ||
      (fd2 = open(output_file, O_RDWR | O_CREAT, 0666)) < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  while ((n = read(fd, buffer, 100)) > 0) {
    if (n_reads % 2 == 0) {
      write(fd2, "Even Read!\n", 10);
    } else {
      write(fd2, buffer, n);
      write(fd2, "\n", 1);
    }
    n_reads++;
  }

  if (close(fd) < 0 || close(fd2) < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
