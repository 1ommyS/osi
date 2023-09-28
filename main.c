#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sys/wait.h"

const int MAX_LENGTH_OF_LINE = 30;
const int MAX_AMOUNT_OF_LINES = 100;
const int FILENAME_SIZE = 10;

void handle_error(int result_of_statement) {
  if (result_of_statement == -1) {
    perror("error with creating: ");
    exit(-1);
  }
}

pid_t try_to_create_proccess() {
  pid_t proccess_id = fork();
  handle_error(proccess_id);
  return proccess_id;
}

int main() {
  char file_first_name[FILENAME_SIZE];
  char file_second_name[FILENAME_SIZE];

  char lines[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE];

  printf("Имя первого файла: ");
  scanf("%s", &file_first_name);
  printf("Имя второго файла: ");
  scanf("%s", &file_second_name);

  int amount_lines;
  printf("Теперь введите количество строк. Оно должно быть меньше %d :",
         MAX_AMOUNT_OF_LINES);
  scanf("%d", &amount_lines);

  printf("Теперь вводите сами строки.\n");

  char lines_for_first_proccess[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE];
  char lines_for_second_proccess[MAX_AMOUNT_OF_LINES][MAX_LENGTH_OF_LINE];

  int amount_of_lines_for_first_proccess = 0;
  int amount_of_lines_for_second_proccess = 0;

  for (int index_of_current_line = 0; index_of_current_line < amount_lines;
       index_of_current_line++) {
    if (rand() % 100 <= 80) {
      scanf("%s",
            lines_for_first_proccess[amount_of_lines_for_first_proccess++]);
    } else {
      scanf("%s",
            lines_for_second_proccess[amount_of_lines_for_second_proccess++]);
    }
  }

  lines_for_first_proccess[amount_of_lines_for_first_proccess][0] = EOF;
  lines_for_second_proccess[amount_of_lines_for_second_proccess][0] = EOF;

  int pipe_for_first_child[2];

  handle_error(pipe(pipe_for_first_child));

  pid_t first_proccess_id = try_to_create_proccess();

  if (first_proccess_id == 0) {
    printf("First child has been started.\n");

    close(pipe_for_first_child[1]);
    dup2(pipe_for_first_child[0], STDIN_FILENO);
    execl("./child", "./child", NULL);
  } else {
    printf("parent process\n");

    close(pipe_for_first_child[0]);
    write(pipe_for_first_child[1], &file_first_name, sizeof(file_first_name));

    for (int current_line = 0; current_line < amount_of_lines_for_first_proccess;
         ++current_line) {
      write(pipe_for_first_child[1], &lines_for_first_proccess[current_line],
            sizeof(lines_for_first_proccess[current_line]));
    }
    close(pipe_for_first_child[1]);
    printf("Данные отправились в первый процесс");

    wait(NULL);

    printf("Первый процесс завершилась");
  }

  int pipe_for_second_child[2];

  handle_error(pipe(pipe_for_second_child));

  pid_t second_proccess_id = try_to_create_proccess();

  if (second_proccess_id == 0) {
    printf("Second child has been started.\n");

    close(pipe_for_second_child[1]);
    dup2(pipe_for_second_child[0], STDIN_FILENO);
    execl("./child", "./child", NULL);
  } else {
    printf("parent process\n");

    close(pipe_for_second_child[0]);
    write(pipe_for_second_child[1], &file_second_name, sizeof(file_second_name));

    for (int current_line = 0; current_line < amount_of_lines_for_second_proccess;
         ++current_line) {
      write(pipe_for_second_child[1], &lines_for_second_proccess[current_line],
            sizeof(lines_for_second_proccess[current_line]));
    }
    close(pipe_for_second_child[1]);
    printf("Данные отправились во второй процесс");

    wait(NULL);

    printf("Первый процесс завершилась");
  }
}
