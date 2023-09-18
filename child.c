#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
  char *filename = argv[0];

  FILE *file = fopen(filename, "w+");

  if (file == NULL) {
    printf("Не удалось открыть файл\n");
    return 1;
  } else {
    printf("Файл открыт успешно\n");
  }

  char line[MAX_LINE];
  while (read(STDIN_FILENO, line, 10) > 2) {
    if (strcmp(line, "\n") == 0) {
      continue;
    }

    int len = strlen(line) - 1;
    for (int i = 0; i < len / 2; i++) {
      char temp = line[i];
      line[i] = line[len - i - 1];
      line[len - i - 1] = temp;
    }
    if (strlen(line) > 2) fprintf(file, "%s", line);
  }
  close(STDIN_FILENO);
  fclose(file);
  return 0;
}