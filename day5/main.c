#include "../lib/input.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(char *input) {
  char *token = strtok(input, "\n");

  uint64_t **ranges = malloc(sizeof(uint64_t *) * 256);
  uint64_t *ids_to_check = malloc(sizeof(uint64_t) * 1024);

  int ranges_i = 0;
  int ids_to_check_i = 0;
  while (token != NULL) {
    if (strstr(token, "-") != NULL) {
      char *copy = strdup(token);
      char *from = strtok_r(copy, "-", &copy);
      char *to = strtok_r(NULL, "-", &copy);

      ranges[ranges_i] = malloc(sizeof(uint64_t) * 2);
      ranges[ranges_i][0] = atoll(from);
      ranges[ranges_i][1] = atoll(to);
      ranges_i++;
    } else {
      ids_to_check[ids_to_check_i] = atoll(token);
      ids_to_check_i++;
    }

    token = strtok(NULL, "\n");
  }

  int result = 0;
  for (int k = 0; k < ids_to_check_i; k++) {
    uint64_t id = ids_to_check[k];
    for (int l = 0; l < ranges_i - 1; l++) {
      if (id >= ranges[l][0] && id <= ranges[l][1]) {
        result++;
        break;
      }
    }
  }

  free(ranges);
  free(ids_to_check);

  printf("Result=%d\n", result);
}

void part2(char *input) {
  char *token = strtok(input, "\n");

  uint64_t **ranges = malloc(sizeof(uint64_t *) * 256);
  int ranges_i = 0;
  while (token != NULL) {
    if (strstr(token, "-") != NULL) {
      char *copy = strdup(token);
      char *first = strtok_r(copy, "-", &copy);
      char *second = strtok_r(NULL, "-", &copy);

      ranges[ranges_i] = malloc(sizeof(uint64_t) * 2);
      ranges[ranges_i][0] = atoll(first);
      ranges[ranges_i][1] = atoll(second);
      ranges_i++;
    } else {
      break;
    }

    token = strtok(NULL, "\n");
  }

  int were_changes = 1;
  while (were_changes) {
    were_changes = 0;
    for (int k = 0; k < ranges_i - 1; k++) {
      if (ranges[k] == NULL)
        continue;

      uint64_t range_k_from = ranges[k][0];
      uint64_t range_k_to = ranges[k][1];
      for (int l = k + 1; l < ranges_i; l++) {
        if (ranges[l] == NULL)
          continue;
        uint64_t range_l_from = ranges[l][0];
        uint64_t range_l_to = ranges[l][1];
        if (range_k_from <= range_l_to && range_l_from <= range_k_to) {
          ranges[k][0] =
              range_k_from < range_l_from ? range_k_from : range_l_from;
          ranges[k][1] = range_k_to > range_l_to ? range_k_to : range_l_to;
          ranges[l] = NULL;

          were_changes = 1;
          goto end_of_while;
        }
      }
    }

  end_of_while:;
  }

  uintmax_t result = 0;
  for (int k = 0; k < ranges_i; k++) {
    if (ranges[k] == NULL)
      continue;

    result += ranges[k][1] - ranges[k][0] + 1;
  }

  free(ranges);

  printf("Result=%ju\n", result);
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
