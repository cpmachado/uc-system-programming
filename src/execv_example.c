/* Copyright © 2024 cpmachado */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int errno;

int main(int argc, char *argv[]) {
  pid_t pid, z;
  char *arg[1] = {0};

  if (argc != 2) {
    printf("Need program to run\nUsage: %s\n", *argv);
    exit(EXIT_FAILURE);
  }

  switch (pid = fork()) {
  case 0:
    printf("CHILD PROCESS\n");
    if (execv(argv[1], arg) == -1) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    break;
  case -1:
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  default:
    break;
  }

  if (wait(&z) < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
