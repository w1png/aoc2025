#include "../lib/input.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(char *input) {
  uint64_t result = 0;

  int numbers[4][1000] = {0};
  int total_rows = 0;
  int total_cols = 0;

  char operations[1000] = {0};
  int total_operations = 0;

  char *line = strtok(input, "\n");
  while (line != NULL) {
    total_cols = 0;
    char *line_copy = strdup(line);
    char *token = strtok_r(line_copy, " ", &line);
    while (token != NULL) {
      if (token[0] == '*' || token[0] == '+') {
        operations[total_operations++] = token[0];
      } else {
        int number = atoi(token);
        numbers[total_rows][total_cols++] = number;
      }

      token = strtok_r(NULL, " ", &line);
    }

    line = strtok(NULL, "\n");
    total_rows++;
  }

  for (int i = 0; i < total_operations; i++) {
    uint64_t intermediate = numbers[0][i];
    for (int j = 1; j < total_rows - 1; j++) {
      if (operations[i] == '*') {
        intermediate *= numbers[j][i];
      } else if (operations[i] == '+') {
        intermediate += numbers[j][i];
      }
    }

    result += intermediate;
  }

  printf("Result=%llu\n", result);
}

char *space_pad_start(char *str, int len) {
  if (!str)
    return NULL;
  if (len <= 0)
    return NULL;

  size_t old_len = strlen(str);

  if (old_len >= (size_t)len) {
    char *copy = malloc(old_len + 1);
    if (copy)
      strcpy(copy, str);
    return copy;
  }

  size_t padding = (size_t)len - old_len;

  char *result = malloc(len + 1); // +1 for null terminator
  if (!result)
    return NULL;

  // Fill with spaces
  memset(result, ' ', padding);

  // Copy original string after the padding
  memcpy(result + padding, str, old_len);

  // Null terminate
  result[len] = '\0';

  return result;
}

void part2(char *input) {
  uint64_t result = 0;

  char *tokens[4][1000] = {0};
  int total_rows = 0;
  int total_cols = 0;
  int longest_number = 0;

  char operations[1000] = {0};
  int total_operations = 0;

  char *line = strtok(input, "\n");
  while (line != NULL) {
    total_cols = 0;
    char *line_copy = strdup(line);
    char *token = strtok_r(line_copy, " ", &line);
    while (token != NULL) {
      if (token[0] == '*' || token[0] == '+') {
        operations[total_operations++] = token[0];
      } else {
        tokens[total_rows][total_cols++] = token;
        int len = strlen(token);
        if (len > longest_number) {
          longest_number = len;
        }
      }

      token = strtok_r(NULL, " ", &line);
    }

    line = strtok(NULL, "\n");
    total_rows++;
  }

  for (int col_index = 0; col_index < total_operations; col_index++) {
    char operation = operations[col_index];

    uint64_t intermediate = 0;
    for (int char_index = longest_number - 1; char_index >= 0; char_index--) {
      int curr = 0;
      // if tokens[j][k] doesnt exist then skip to next one.
      // if it exists then conver this char to a number and add pow(10, k)
      for (int row_index = 0; row_index < total_rows - 1; row_index++) {
        char *padded =
            space_pad_start(tokens[row_index][col_index], longest_number);
        // printf("padded[%d]='%c'; \n", char_index, padded[char_index]);
        char c = padded[char_index];
        if (c == ' ')
          continue;
        // convert c to number
        int number = c - '0';
        curr = curr * 10 + number;
      }
      printf("curr = %d\n", curr);

      if (operation == '*') {
        if (intermediate == 0) {
          intermediate = curr;
        } else {
          intermediate *= curr;
        }
      } else if (operation == '+') {
        intermediate += curr;
      }
    }
    printf("operator = %c\n", operation);
    printf("intermediate = %llu\n", intermediate);

    result += intermediate;

    // printf("%c\t", operation);
    printf("\n");
  }

  // for (int i = 0; i < total_operations; i++) {
  //   uint64_t intermediate = numbers[0][i];
  //   for (int j = 1; j < total_rows - 1; j++) {
  //     if (operations[i] == '*') {
  //       intermediate *= numbers[j][i];
  //     } else if (operations[i] == '+') {
  //       intermediate += numbers[j][i];
  //     }
  //   }
  //
  //   result += intermediate;
  // }

  printf("Result=%llu\n", result);
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
