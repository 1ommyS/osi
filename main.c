#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE 9

// Structure to hold complex numbers
typedef struct {
  double real;
  double imag;
} Complex;

typedef struct {
  Complex** matrix;
  int rows;
  int cols;
} Matrix;

typedef struct {
  Matrix* matrix1;
  Matrix* matrix2;
  Matrix* result;
  int startRow;
  int endRow;
} ThreadArgs;

Matrix* createMatrix(int rows, int cols) {
  Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
  matrix->rows = rows;
  matrix->cols = cols;
  matrix->matrix = (Complex**)malloc(rows * sizeof(Complex*));
  for (int i = 0; i < rows; i++) {
    matrix->matrix[i] = (Complex*)malloc(cols * sizeof(Complex));
  }
  return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(Matrix* matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    free(matrix->matrix[i]);
  }
  free(matrix->matrix);
  free(matrix);
}

// Function to multiply two complex numbers
Complex multiplyComplex(Complex num1, Complex num2) {
  Complex result;
  result.real = num1.real * num2.real - num1.imag * num2.imag;
  result.imag = num1.real * num2.imag + num1.imag * num2.real;
  return result;
}

void* multiplyRow(void* arguments) {
  ThreadArgs* args = (ThreadArgs*)arguments;
  for (int i = args->startRow; i <= args->endRow; i++) {
    for (int j = 0; j < args->matrix2->cols; j++) {
      args->result->matrix[i][j] = (Complex){0, 0};
      for (int k = 0; k < args->matrix1->cols; k++) {
        Complex product = multiplyComplex(args->matrix1->matrix[i][k],
                                          args->matrix2->matrix[k][j]);
        args->result->matrix[i][j].real += product.real;
        args->result->matrix[i][j].imag += product.imag;
      }
    }
  }
  pthread_exit(NULL);
}
int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: %s <num_threads>\n", argv[0]);
    return 1;
  }
  struct timeval start, end;
  gettimeofday(&start, NULL);

  int numThreads = atoi(argv[1]);

  // Create matrices
  Matrix* matrix1 = createMatrix(SIZE, SIZE);
  Matrix* matrix2 = createMatrix(SIZE, SIZE);
  Matrix* result = createMatrix(SIZE, SIZE);

  // Initialize matrices with random complex numbers
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      matrix1->matrix[i][j].real = (i + 1) * (j + 1);
      matrix1->matrix[i][j].imag = (i + 1) * (j + 1);
      matrix2->matrix[i][j].real = 2 * (i + 1) + 3 * (j + 1);
      matrix2->matrix[i][j].imag = (i + 1) + (j + 1);
    }
  }

  // Create threads
  pthread_t threads[numThreads];
  ThreadArgs threadArgs[numThreads];
  int rowsPerThread = SIZE / numThreads;
  int remainingRows = SIZE % numThreads;
  int startRow = 0;
  int endRow = -1;

  for (int i = 0; i < numThreads; i++) {
    startRow = endRow + 1;
    endRow = startRow + rowsPerThread - 1;
    if (remainingRows > 0) {
      endRow++;
      remainingRows--;
    }
    
    threadArgs[i].matrix1 = matrix1;
    threadArgs[i].matrix2 = matrix2;
    threadArgs[i].result = result;
    threadArgs[i].startRow = startRow;
    threadArgs[i].endRow = endRow;
    pthread_create(&threads[i], NULL, multiplyRow, (void*)&threadArgs[i]);
  }
  for (int i = 0; i < numThreads; i++) {
    pthread_join(threads[i], NULL);
  }

  // Print the result matrix
  printf("Result:\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%.2f + %.2fi\t", result->matrix[i][j].real,
             result->matrix[i][j].imag);
    }
    printf("\n");
  }

  // Free memory
  freeMatrix(matrix1);
  freeMatrix(matrix2);
  freeMatrix(result);

  gettimeofday(&end, NULL);
  double executionTime =
      (end.tv_sec - start.tv_sec) * 1000.0;  // seconds to milliseconds
  executionTime +=
      (end.tv_usec - start.tv_usec) / 1000.0;  // microseconds to milliseconds
  printf("Execution time: %.20f ms\n", executionTime);

  return 0;
}