#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Input *read_input(char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file %s\n", file_name);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char *input = malloc(size + 1);
  if (input == NULL) {
    fprintf(stderr, "Could not allocate memory for input\n");
    exit(1);
  }

  size_t read = fread(input, 1, size, file);
  if (read != size) {
    fprintf(stderr, "Could not read input\n");
    exit(1);
  }
  input[size] = '\0';

  fclose(file);

  Input *result = malloc(sizeof(Input));
  if (result == NULL) {
    fprintf(stderr, "Could not allocate memory for input\n");
    exit(1);
  }
  result->input = input;
  result->size = size;

  return result;
}
