#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>

const char* NAME_OF_SHARES_MEMORY_FIRST = "share_memory_first";
const char* NAME_OF_SHARES_MEMORY_SECOND = "share_memory_second";
const char* NAME_SEMAPHORE_FIRST = "semaphore_first";
const char* NAME_SEMAPHORE_SECOND = "semaphore_second";
const int MODE = 0666;
const int SHARED_MEMORY_SIZE = 4096;
const int MAX_SIZE_OF_STRING = 50;

void handle_error(bool result_of_statement, char* string) {
    if (result_of_statement) {
        write(STDERR_FILENO, string, strlen(string) * sizeof(char));
        shm_unlink(NAME_OF_SHARES_MEMORY_FIRST);
        shm_unlink(NAME_OF_SHARES_MEMORY_SECOND);
        sem_unlink(NAME_SEMAPHORE_FIRST);
        sem_unlink(NAME_SEMAPHORE_SECOND);
        exit(-1);
    }
}

void correct_file_name(char* string) {
    for (unsigned long symbol_index = 0; symbol_index < strlen(string); ++symbol_index) {
        if (string[symbol_index] == '\n') {
            string[symbol_index] = '\0';
            return;
        }
    }
}

int main() {

    int file_descriptor_first = shm_open(NAME_OF_SHARES_MEMORY_FIRST, O_CREAT | O_RDWR, MODE);
    handle_error(file_descriptor_first == -1, "error shm_open first");
    handle_error(ftruncate(file_descriptor_first, SHARED_MEMORY_SIZE) == -1, "error truncate first");

    void* data_exchange_first = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                                     file_descriptor_first, 0);
    handle_error(data_exchange_first == MAP_FAILED, "error mmap first");
    strcpy(data_exchange_first, "\0");


    int file_descriptor_second = shm_open(NAME_OF_SHARES_MEMORY_SECOND, O_CREAT | O_RDWR, MODE);
    handle_error(file_descriptor_second == -1, "error shm_open second");
    handle_error(ftruncate(file_descriptor_second, SHARED_MEMORY_SIZE) == -1, "error truncate second");

    void* data_exchange_second = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                                      file_descriptor_second, 0);
    handle_error(data_exchange_second == MAP_FAILED, "error mmap second");
    strcpy(data_exchange_first, "\0");


    printf("Enter file1 name\n");
    char file_name_first[MAX_SIZE_OF_STRING];
    handle_error(read(STDIN_FILENO, file_name_first, sizeof(file_name_first)) <= 0,
                 "error reading from stdin first file");
    correct_file_name(file_name_first);

    printf("Enter file2 name\n");
    char file_name_second[MAX_SIZE_OF_STRING];
    handle_error(read(STDIN_FILENO, file_name_second, sizeof(file_name_second)) <= 0,
                 "error reading from stdin second file");
    correct_file_name(file_name_second);

    sem_t* semaphore_first = sem_open(NAME_SEMAPHORE_FIRST, O_CREAT, MODE, 0);
    handle_error(semaphore_first == SEM_FAILED, "error sem_open first");

    sem_t* semaphore_second = sem_open(NAME_SEMAPHORE_SECOND, O_CREAT, MODE, 0);
    handle_error(semaphore_second == SEM_FAILED, "error sem_open second");

    pid_t process_id_first = fork();
    handle_error(process_id_first < 0, "error process creation first");

    if (process_id_first == 0) {
        handle_error(execl("child", "first", file_name_first, NULL) < 0, "error child process startup first");
    } else {
        pid_t process_id_second = fork();
        handle_error(process_id_second < 0, "error process creation second");

        if (process_id_second == 0) {
            handle_error(execl("child", "second", file_name_second, NULL) < 0, "error child process startup second");
        } else {
            printf("Введите количество строк для обработки:\n");
            int number_of_rows;
            char enter;
            scanf("%d%c", &number_of_rows, &enter);

            for (int index_of_rows = 0; index_of_rows < number_of_rows; ++index_of_rows) {

                char buffer[MAX_SIZE_OF_STRING];
                fgets(buffer, MAX_SIZE_OF_STRING, stdin);
                correct_file_name(buffer);

                int rand = arc4random() % 100;
                if (rand <= 80) {
                    sprintf(data_exchange_first, "%s", buffer);
                    sem_post(semaphore_first);
                    sem_wait(semaphore_first);
                } else {
                    sprintf(data_exchange_second, "%s", buffer);
                    sem_post(semaphore_second);
                    sem_wait(semaphore_second);
                }
            }

            printf("Все строки кончились, программа заканчивается\n");
            sprintf(data_exchange_first, "%s", "\0");
            sprintf(data_exchange_second, "%s", "\0");

        }
    }

    sem_close(semaphore_first);
    sem_close(semaphore_second);
    sem_unlink(NAME_SEMAPHORE_FIRST);
    sem_unlink(NAME_SEMAPHORE_SECOND);

    shm_unlink(NAME_OF_SHARES_MEMORY_FIRST);
    shm_unlink(NAME_OF_SHARES_MEMORY_SECOND);
    return 0;
}