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

void reverse(char* string) {
    int length = strlen(string);

    for (int begin_index = 0, end_index = length - 1; begin_index < end_index; ++begin_index, --end_index) {
        char temp = string[begin_index];
        string[begin_index] = string[end_index];
        string[end_index] = temp;
    }
}

int main(int argc, char* argv[]) {
    char* argument = argv[0];
    char* file_name = argv[1];

    int file_descriptor = 0;
    sem_t* semaphore = NULL;

    if (strcmp(argument, "first") == 0) {
        file_descriptor = shm_open(NAME_OF_SHARES_MEMORY_FIRST, O_CREAT | O_RDWR, MODE);
        handle_error(file_descriptor == -1, "error shm_open child first");

        semaphore = sem_open(NAME_SEMAPHORE_FIRST, O_CREAT, MODE, 0);
        handle_error(semaphore == SEM_FAILED, "error sem_open child first");

    } else if (strcmp(argument, "second") == 0) {

        file_descriptor = shm_open(NAME_OF_SHARES_MEMORY_SECOND, O_CREAT | O_RDWR, MODE);
        handle_error(file_descriptor == -1, "error shm_open child second");

        semaphore = sem_open(NAME_SEMAPHORE_SECOND, O_CREAT, MODE, 0);
        handle_error(semaphore == SEM_FAILED, "error sem_open child second");

    } else {
        handle_error(true, "error argument");
    }

    void* data_exchange = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

    while (true) {
        sem_wait(semaphore);
        char* input_string = (char*) data_exchange;
        if (strcmp(input_string, "\0") == 0) {
            break;
        }
        FILE* file = fopen(file_name, "a");
        if (file == NULL) {
            printf("Failed to open the file. Exiting.\n");
        } else {
            printf("File was successfully open");
        }
        reverse(input_string);
        fprintf(file, "%s\n", input_string);
        fclose(file);

        sem_post(semaphore);
    }
    sem_post(semaphore);
    sem_close(semaphore);
    return 0;
}