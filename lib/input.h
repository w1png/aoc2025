#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

typedef struct {
  char *input;
  size_t size;
} Input;

Input *read_input(char *file_name);

#endif
