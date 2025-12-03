#include "../lib/input.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

int get_first_largest_digit(char *token, size_t *max_i, size_t limit) {
  int max = 0;

  char *token_copy = malloc(limit + 1);
  strncpy(token_copy, token, strlen(token));
  printf("token_copy=%s\n", token_copy);
  for (size_t i = 0; i < limit; i++) {
    int curr = token_copy[i] - '0';
    printf("%d\n", curr);

    if (curr > max) {
      max = curr;
      if (max_i != NULL) {
        *max_i = i;
      }
    }
  }

  return max;
}

void part1(char *input) {
  int result = 0;

  char *token = strtok(input, "\n");
  while (token != NULL) {
    size_t token_length = strlen(token);

    size_t max_dozens_i;
    int max_dozens =
        get_first_largest_digit(token, &max_dozens_i, strlen(token) - 1);

    char *token_copy = malloc(token_length + 1);
    strncpy(token_copy, token + max_dozens_i + 1, token_length - max_dozens_i);
    int max = get_first_largest_digit(token_copy, NULL, strlen(token_copy));

    result += (max_dozens * 10) + max;

    token = strtok(NULL, "\n");
  }

  printf("Result = %d\n", result);
}

void part2(char *input) {
  long long result = 0;

  char *token = strtok(input, "\n");
  while (token != NULL) {
  }

  printf("Result = %lld\n", result);
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
