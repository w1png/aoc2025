#include "../lib/input.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(char *input) {
  char *token = strtok(input, ",");

  long long total = 0;

  while (token != NULL) {
    char *temp = strdup(token);

    char *first = strtok_r(temp, "-", &token);
    char *second = strtok_r(NULL, "-", &token);
    long long start = strtoll(first, NULL, 10);
    long long end = strtoll(second, NULL, 10);

    char *iStr = NULL;
    for (long long i = start; i <= end; i++) {
      iStr = malloc(sizeof(char) * 16);
      sprintf(iStr, "%lld", i);

      int len = strlen(iStr);
      if (len % 2 != 0) {
        continue;
      }

      int half_len = len / 2;
      char *first_half = malloc(sizeof(char) * half_len);
      strncpy(first_half, iStr, half_len);

      char *second_half = malloc(sizeof(char) * half_len);
      strncpy(second_half, iStr + half_len, half_len);

      if (strcmp(first_half, second_half) == 0) {
        total += i;
      }

      free(iStr);
      free(first_half);
      free(second_half);
    }

    free(temp);
    token = strtok(NULL, ",");
  }

  printf("total=%lld\n", total);
}

void part2(char *input) {
  char *token = strtok(input, ",");

  long long total = 0;

  while (token != NULL) {
    char *temp = strdup(token);

    char *first = strtok_r(temp, "-", &token);
    char *second = strtok_r(NULL, "-", &token);

    long long start = strtoll(first, NULL, 10);
    long long end = strtoll(second, NULL, 10);

    for (long long i = start; i <= end; i++) {
      char *iStr = malloc(sizeof(char) * 16);
      sprintf(iStr, "%lld", i);

      int len = strlen(iStr);

      for (int j = 1; j < (len / 2) + 1; j++) {
        char *prefix = malloc(sizeof(char) * j + 1);
        strncpy(prefix, iStr, j);

        int times = len / j;
        char *new_str = malloc(sizeof(char) * (j * times) + 1);
        for (int k = 0; k < times; k++) {
          strncpy(new_str + k * j, prefix, j);
        }

        if (strcmp(new_str, iStr) == 0) {
          total += i;
          break;
        }
      }

      free(iStr);
    }
    free(temp);
    token = strtok(NULL, ",");
  }

  printf("result=%lld\n", total);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    return 1;
  }

  Input *input = read_input(argv[1]);

  if (strcmp(argv[2], "1") == 0) {
    part1(input->input);
  } else if (strcmp(argv[2], "2") == 0) {
    part2(input->input);
  } else {
    fprintf(stderr, "Invalid part number %s\n", argv[2]);
    return 1;
  }
}
