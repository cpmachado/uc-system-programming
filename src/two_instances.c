/* Copyright © 2024 cpmachado */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int val1;
  int val2;

  if (argc != 3) {
    printf("Need two integer values.\nUsage: %s <val1> <val2>\n", *argv);
    exit(EXIT_FAILURE);
  }

  val1 = atoi(argv[1]);
  val2 = atoi(argv[2]);

  while (1) {
    printf("Val1: %d  \t  location %p \t Val2: %d  \t  location %p\n", val1,
           (void *)&val1, val2, (void *)&val2);
  }

  return 0;
}
