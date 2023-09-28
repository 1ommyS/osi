#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
  char *filename = argv[0];

  int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if (file == -1) {
    printf("Не удалось открыть файл\n");
    return 1;
  } else {
    printf("Файл открыт успешно\n");
  }

  char line[MAX_LINE];
  ssize_t bytesRead;

  while ((bytesRead = read(STDIN_FILENO, line, sizeof(line))) > 2) {
    if (strcmp(line, "\n") == 0) {
      continue;
    }
    /*
    int len = strlen(line) - 1;
    for (int i = 0; i < len / 2; i++) {
      char temp = line[i];
      line[i] = line[len - i - 1];
      line[len - i - 1] = temp;
    }
    */

        if (strlen(line) > 2) {
      write(file, line, bytesRead);
    }
  }

  close(file);

  return 0;
}