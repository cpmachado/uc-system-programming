/* Copyright © 2024 cpmachado */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *threadSafe(void *unused) {
  (void)unused;
  printf("Hello from the thread!\n");
  return NULL;
}

int main() {
  pthread_t id;
  int error;

  printf("Not in the thread\n");
  if ((error = pthread_create(&id, NULL, threadSafe, NULL)) ||
      (error = pthread_join(id, NULL))) {
    printf("%s\n", strerror(error));
    exit(EXIT_FAILURE);
  }
  printf("After thread finished\n");

  return 0;
}
