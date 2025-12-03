#include "../lib/input.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

int get_first_largest_digit(char *token, size_t *max_i,
                            size_t digits_remaining) {
  int max = 0;

  char *token_copy = malloc(strlen(token) + 1);
  strncpy(token_copy, token, strlen(token));
  for (size_t i = 0; i < digits_remaining; i++) {
    int curr = token_copy[i] - '0';

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
    size_t i;
    int max_dozens = get_first_largest_digit(token, &i, strlen(token) - 1);

    token += i + 1;
    int max = get_first_largest_digit(token, NULL, strlen(token));

    result += (max_dozens * 10) + max;

    token = strtok(NULL, "\n");
  }

  printf("Result = %d\n", result);
}

void part2(char *input) {
  long long result = 0;

  char *token = strtok(input, "\n");

  while (token != NULL) {
    size_t prev_index = 0;
    long long curr = 0;

    for (int i = 0; i < 12; i++) {
      int digits_remaining = strlen(token) - 11 + i;
      int first = get_first_largest_digit(token, &prev_index, digits_remaining);

      curr += first * pow(10, 11 - i);
      token += prev_index + 1;
    }

    result += curr;

    token = strtok(NULL, "\n");
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
