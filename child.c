#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int MAX_LENGTH_OF_LINE = 30;
const int MAX_AMOUNT_OF_LINES = 100;
const int FILENAME_SIZE = 10;

void reverse_lines(char* lines) {
  int len = strlen(lines);
  for (int i = 0; i < len / 2; i++) {
    char temp = lines[i];
    lines[i] = lines[len - i - 1];
    lines[len - i - 1] = temp;
  }
}

void write_lines_to_file(char lines[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE], char filename[FILENAME_SIZE]) {
  FILE* file = open(filename, "w");

  if (file == NULL) {
    printf("file wasn't open");
    exit(-1);
  }

  for (int index_of_line = 0; index_of_line < MAX_AMOUNT_OF_LINES && lines[index_of_line][0] != EOF; ++index_of_line) {
    fprintf(file, "%s\n", lines[index_of_line]);
    printf("%s\n", lines[index_of_line]);
  }

  fclose(file);
}

int main() {
  char filename[FILENAME_SIZE];
  read(STDIN_FILENO, &filename, sizeof(filename));

  char lines[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE];
  for (int amount_of_line_from_input = 0;
       amount_of_line_from_input < MAX_AMOUNT_OF_LINES;
       amount_of_line_from_input++) {
    read(STDIN_FILENO, lines[amount_of_line_from_input],
         sizeof(lines[amount_of_line_from_input]));
  }

  reverse_lines(lines);

  write_lines_to_file(lines, filename);
}