#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error_processing(bool exception, char *bug_report) {
    if (exception) {
        write(STDERR_FILENO, bug_report, strlen(bug_report) * sizeof(char));
        exit(-1);
    }
}

int main() {
    int pipe1[2];
    int pipe2[2];

    error_processing((pipe(pipe1) == -1), "Error with opening pipe 1");
    error_processing((pipe(pipe2) == -1), "Error with opening pipe 2");

    char name_file_first[10];
    char name_file_second[10];


    error_processing(read(STDIN_FILENO, name_file_first, sizeof(name_file_first)) == -1,
                     "error with reading file 1");
    error_processing(read(STDIN_FILENO, name_file_second, sizeof(name_file_second)) == -1,
                     "error with reading file 2");

    for (size_t i = 0; i < sizeof(name_file_first); i++) {
        if (name_file_first[i] == '\n') {
            name_file_first[i] = '\0';
            break;
        }
    }

    for (size_t i = 0; i < sizeof(name_file_second); i++) {
        if (name_file_second[i] == '\n') {
            name_file_second[i] = '\0';
            break;
        }
    }

    pid_t channel_1 = fork();
    error_processing((channel_1 == -1), "channel 1 doesnt work");

    if (channel_1 == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        error_processing(dup2(pipe1[0], STDIN_FILENO) < 0,
                         "dup2 doesnt work with channel 1");
        error_processing((execl("child", name_file_first, NULL) < 0),
                         "Дочерний не воркает");
    } else {

        pid_t channel_2 = fork();
        error_processing((channel_2 == -1), "channel 2 doesnt work");

        if (channel_2 == 0) {
            close(pipe2[1]);
            close(pipe1[0]);
            close(pipe1[1]);
            error_processing(dup2(pipe2[0], STDIN_FILENO) < 0,
                             "dup2 doesnt work with channel 2");
            error_processing((execl("child", name_file_second, NULL) < 0),
                             "Дочерний не воркает");
        } else {

            close(pipe1[0]);  // Закрываем запись в pipe1
            close(pipe2[0]);  // Закрываем запись в pipe2

            char line[50];

            while (scanf("%s", line) != EOF) {
                line[strlen(line)] = '\n';
                if (rand() % 100 < 80) {
                    write(pipe1[1], line, strlen(line));
                } else {
                    write(pipe2[1], line, strlen(line));
                }
            }
        }
    }
    close(pipe1[1]);
    close(pipe1[0]);
    close(pipe2[1]);
    close(pipe2[0]);
}