#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int MAX_LENGTH_OF_LINE = 30;
const int MAX_AMOUNT_OF_LINES = 100;
const int FILENAME_SIZE = 10;

size_t strlen(const char *str) {
    size_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}
void reverse_lines(char lines[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE], int len) {
    for (int i = 0; i < len; i++) {
        int start = 0;
        int end = strlen(lines[i]) - 1;
        while (start < end) {
            char temp = lines[i][start];
            lines[i][start] = lines[i][end];
            lines[i][end] = temp;
            start++;
            end--;
        }
    }
}
void write_lines_to_file(char lines[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE],
                         char filename[FILENAME_SIZE], int len) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Failed to open the file. Exiting.\n");
        exit(-1);
    } else {
        printf("File opened successfully.\n");
    }

    for (int index_of_line = 0;
         index_of_line < len && lines[index_of_line][0] != EOF; ++index_of_line) {
        fprintf(file, "%s\n", lines[index_of_line]);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int amount_of_lines = atoi(argv[0]);

    char filename[FILENAME_SIZE];
    read(STDIN_FILENO, &filename, sizeof(filename));

    char lines[amount_of_lines][MAX_LENGTH_OF_LINE];
    for (int amount_of_line_from_input = 0;
         amount_of_line_from_input < amount_of_lines;
         amount_of_line_from_input++) {
        read(STDIN_FILENO, lines[amount_of_line_from_input],
             sizeof(lines[amount_of_line_from_input]));
    }

    reverse_lines(lines, amount_of_lines);

    printf("Реверсированные строки:\n");
    for (int line_index = 0; line_index < amount_of_lines; line_index++) {
        printf("%s\n", lines[line_index]);
    }

    write_lines_to_file(lines, filename, amount_of_lines);
    close(STDIN_FILENO);
}