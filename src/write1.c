/* Copyright © 2024 cpmachado */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

int main(void) {
  /* No need to be executable*/
  int file = open("myFile.txt", O_RDWR | O_CREAT, 0644);
  char *str = "I am writing to the file";
  int n;

  if (file < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  n = write(file, str, strlen(str));

  if (n < 0 || close(file)) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
