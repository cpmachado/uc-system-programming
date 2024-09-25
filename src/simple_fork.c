/* Copyright © 2024 cpmachado */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int errno;

int main() {
  pid_t pid = fork();

  // Child Process
  switch (pid) {
  case 0:
    printf("Hello from the Child --- PID: %d ---- Parent PID: %d\n", getpid(),
           getppid());
    sleep(4);
    printf("Child woke up\n");
    break;
  case -1:
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  default:
    wait(NULL);
    printf("Hello from the Parent --- PID: %d ---- Child PID: %d\n", getpid(),
           pid);
  }

  return 0;
}
