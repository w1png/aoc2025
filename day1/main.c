#include "../lib/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(char *input) {
  printf("Part 1 of day 1 input=%s\n", input);
  int result = 0;
  int curr_degrees = 50;
  char *token = strtok(input, "\n");

  while (token != NULL) {
    int delta = token[0] == 'L' ? -1 : 1;

    int rest_int = atoi(token + 1);

    curr_degrees = (curr_degrees + delta * rest_int) % 100;
    if (curr_degrees < 0) {
      curr_degrees = 100 + curr_degrees;
    }

    if (curr_degrees == 0) {
      result++;
    }

    token = strtok(NULL, "\n");
  }

  printf("Result=%d\n", result);
}

void part2(char *input) {
  int result = 0;
  int curr_degrees = 50;
  char *token = strtok(input, "\n");

  while (token != NULL) {
    int delta = token[0] == 'L' ? -1 : 1;

    int rest_int = atoi(token + 1);

    for (int i = 0; i < rest_int; i++) {
      curr_degrees = (curr_degrees + delta) % 100;

      if (curr_degrees == 0) {
        result++;
      }
    }

    token = strtok(NULL, "\n");
  }

  printf("Result=%d\n", result);
}

// void part2(char *input) {
//   int result = 0;
//   int curr_degrees = 50;
//   char *token = strtok(input, "\n");
//
//   while (token != NULL) {
//     int delta = 1;
//     char first = token[0];
//     if (first == 'L') {
//       delta = -1;
//     }
//
//     char *rest = token + 1;
//     int rest_int = atoi(rest);
//     int was_zero = curr_degrees == 0;
//
//     int over = floor((double)rest_int / 100);
//     int additional_rotations = (rest_int > 100 ? over : 0);
//
//     curr_degrees += delta * rest_int;
//     if (curr_degrees < 0) {
//       if (!was_zero) {
//         if ((over * 100 + curr_degrees) < 0) {
//           additional_rotations++;
//           printf("Добавляем доп поворот\n");
//         }
//         result += additional_rotations;
//
//         printf("(+) token %s повернул отрицательно через 0 + "
//                "доп_повороты=%d (сейчас=%d) (поворотов всего=%d)\n",
//                token, additional_rotations, curr_degrees, result);
//       } else {
//         printf("(-) %s НЕ повернул (сейчас градусов=%d) (поворотов
//         всего=%d)\n",
//                token, curr_degrees, result);
//       }
//       curr_degrees = 100 + (curr_degrees % 100);
//     } else if (curr_degrees >= 100) {
//       if (curr_degrees - (over * 100) >= 100) {
//         additional_rotations++;
//         printf("Добавляем доп поворот\n");
//       }
//
//       result += additional_rotations;
//
//       printf("(+) %s повернул положительно через 0 + "
//              "доп_повороты=%d (сейчас градусов=%d) (поворотов всего=%d)\n",
//              token, additional_rotations, curr_degrees, result);
//     } else if (curr_degrees != 0) {
//       printf("(-) %s НЕ повернул (сейчас градусов=%d) (поворотов
//       всего=%d)\n",
//              token, curr_degrees, result);
//     }
//
//     curr_degrees = curr_degrees % 100;
//
//     if (curr_degrees == 0) {
//       result++;
//
//       printf("(+) %s повернул в 0 + "
//              "доп_повороты=%d (сейчас градусов=%d) (поворотов всего=%d)\n",
//              token, additional_rotations, curr_degrees, result);
//     }
//
//     printf("сейчас градусов=%d (после итерации)\n\n", curr_degrees);
//
//     token = strtok(NULL, "\n");
//   }
//
//   printf("Result=%d\n", result);
// }

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
