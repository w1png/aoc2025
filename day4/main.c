#include "../lib/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(char *input) {
  printf("Part 1 of day 1 input=%s\n", input);

  int result = 0;

  int rolls[256][256] = {0};

  char *token = strtok(input, "\n");
  int i = 0;
  while (token != NULL) {
    for (size_t j = 0; j < strlen(token); j++) {
      rolls[i][j] = token[j] == '@';
    }

    i++;
    token = strtok(NULL, "\n");
  }

  for (int j = 0; j < i; j++) {
    for (int k = 0; k < i; k++) {
      if (!rolls[j][k])
        continue;

      int total_surrounding = 0;

      if (j != 0) {
        total_surrounding += rolls[j - 1][k];
        if (k != 0) {
          total_surrounding += rolls[j - 1][k - 1];
        }
        if (k != i) {
          total_surrounding += rolls[j - 1][k + 1];
        }
      }

      if (k != 0) {
        total_surrounding += rolls[j][k - 1];
      }

      if (k != i) {
        total_surrounding += rolls[j][k + 1];
      }

      if (j != i) {
        total_surrounding += rolls[j + 1][k];
        if (k != 0) {
          total_surrounding += rolls[j + 1][k - 1];
        }
        if (k != i) {
          total_surrounding += rolls[j + 1][k + 1];
        }
      }

      if (total_surrounding < 4) {
        result++;
      }
    }
  }

  printf("Result=%d\n", result);
}

void part2(char *input) {
  int result = 0;

  int rolls[256][256] = {0};

  char *token = strtok(input, "\n");
  int i = 0;
  while (token != NULL) {
    for (size_t j = 0; j < strlen(token); j++) {
      rolls[i][j] = token[j] == '@';
    }

    i++;
    token = strtok(NULL, "\n");
  }

  int was_changed = 1;
  while (was_changed) {
    was_changed = 0;

    for (int j = 0; j < i; j++) {
      for (int k = 0; k < i; k++) {
        if (!rolls[j][k])
          continue;

        int total_surrounding = 0;

        if (j != 0) {
          total_surrounding += rolls[j - 1][k];
          if (k != 0) {
            total_surrounding += rolls[j - 1][k - 1];
          }
          if (k != i) {
            total_surrounding += rolls[j - 1][k + 1];
          }
        }

        if (k != 0) {
          total_surrounding += rolls[j][k - 1];
        }

        if (k != i) {
          total_surrounding += rolls[j][k + 1];
        }

        if (j != i) {
          total_surrounding += rolls[j + 1][k];
          if (k != 0) {
            total_surrounding += rolls[j + 1][k - 1];
          }
          if (k != i) {
            total_surrounding += rolls[j + 1][k + 1];
          }
        }

        if (total_surrounding < 4) {
          was_changed = 1;
          rolls[j][k] = 0;
          result++;
        }
      }
    }
  }

  printf("Result=%d\n", result);
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
