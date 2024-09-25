/* Copyright © 2024 cpmachado */
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

extern int errno;

pthread_t *producers;
pthread_t *consumers;
sem_t buf_mutex, empty_count, fill_count;
int *buf, buf_pos = -1, prod_count, con_count, buf_len;

int produce(pthread_t self) {
  int i = 0;
  int p = 1 + rand() % 40;
  while (!pthread_equal(*(producers + i), self) && i < prod_count) {
    i++;
  }
  printf("Producer %d produced %d \n", i + 1, p);
  return p;
}

void consume(int p, pthread_t self) {
  int i = 0;
  while (!pthread_equal(*(consumers + i), self) && i < con_count) {
    i++;
  }

  printf("Buffer:");
  for (i = 0; i <= buf_pos; ++i)
    printf("%d ", *(buf + i));
  printf("\nConsumer %d consumed %d \nCurrent buffer len: %d\n", i + 1, p,
         buf_pos);
}

void *producer(void *args) {
  (void)args;

  while (1) {
    int p = produce(pthread_self());
    sem_wait(&empty_count);
    sem_wait(&buf_mutex);
    ++buf_pos;
    *(buf + buf_pos) = p;
    sem_post(&buf_mutex);
    sem_post(&fill_count);
    sleep(1 + rand() % 3);
  }

  return NULL;
}

void *consumer(void *args) {
  int c;

  (void)args;

  while (1) {
    sem_wait(&fill_count);
    sem_wait(&buf_mutex);
    c = *(buf + buf_pos);
    consume(c, pthread_self());
    --buf_pos;
    sem_post(&buf_mutex);
    sem_post(&empty_count);
    sleep(1 + rand() % 5);
  }

  return NULL;
}

int main(void) {
  int i, err;

  srand(time(NULL));

  sem_init(&buf_mutex, 0, 1);
  sem_init(&fill_count, 0, 0);

  // User input
  printf("Enter the number of Producers:");
  scanf("%d", &prod_count);
  if (!(producers = (pthread_t *)malloc(prod_count * sizeof(pthread_t)))) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("Enter the number of Consumers:");
  scanf(" %d", &con_count);
  if (!(consumers = (pthread_t *)malloc(con_count * sizeof(pthread_t)))) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("Enter buffer capacity:");
  scanf("%d", &buf_len);
  if (buf_len <= 0) {
    printf("buffer length = %d <= 0, it needs to be a positive int\n", buf_len);
    exit(EXIT_FAILURE);
  }
  if (!(buf = (int *)malloc(buf_len * sizeof(int)))) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  sem_init(&empty_count, 0, buf_len);

  for (i = 0; i < prod_count; i++) {
    if ((err = pthread_create(&producers[i], NULL, &producer, NULL)) < 0) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < con_count; i++) {
    if ((err = pthread_create(&consumers[i], NULL, &consumer, NULL)) < 0) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < prod_count; i++) {
    if ((err = pthread_join(producers[i], NULL)) < 0) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < con_count; i++) {
    if ((err = pthread_join(consumers[i], NULL)) < 0) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  return 0;
}
