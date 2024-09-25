/* Copyright © 2024 cpmachado */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int NUM_THREADS = 10;

void *ThreadSafe(void *args) {
  int *threadId = (int *)args;
  printf("Hello from Thread: %d\n", *threadId);
  return NULL;
}

int main() {
  int i, j;
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int error;

  printf("Before thread!\n");

  for (i = 0; i < NUM_THREADS; i++) {
    thread_args[i] = i;
    if ((error = pthread_create(&threads[i], NULL, ThreadSafe,
                                (void *)&thread_args[i])) < 0) {
      printf("%s\n", strerror(error));
      exit(EXIT_FAILURE);
    }
  }

  for (j = 0; j < NUM_THREADS; j++) {
    if ((error = pthread_join(threads[j], NULL)) < 0) {
      printf("%s\n", strerror(error));
      exit(EXIT_FAILURE);
    }
  }

  printf("After thread!\n");

  pthread_exit(NULL);

  return 0;
}
