#include "../lib/input.h"
#include <stdio.h>
#include <string.h>

void part1(char *input) { printf("Part 1 of day 1 input=%s\n", input); }

void part2(char *input) { printf("Part 2 of day 1 input=%s\n", input); }

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
