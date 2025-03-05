#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6  // Точность
#define MAX_ITER 1000  // Максимальное количество итераций

// Функция для чтения матрицы и вектора из файла
void readMatrixFromFile(const char* filename, double*** A, double** B, int* N) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    // Чтение размера матрицы
    fscanf(file, "%d", N);

    // Выделение памяти для матрицы A и вектора B
    *A = (double**)malloc((*N) * sizeof(double*));
    for (int i = 0; i < *N; i++) {
        (*A)[i] = (double*)malloc((*N) * sizeof(double));
    }
    *B = (double*)malloc((*N) * sizeof(double));

    // Чтение матрицы A
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            fscanf(file, "%lf", &(*A)[i][j]);
        }
    }

    // Чтение вектора B
    for (int i = 0; i < *N; i++) {
        fscanf(file, "%lf", &(*B)[i]);
    }

    fclose(file);
}

// Метод Зейделя
void seidel(double** A, double* B, double* X, int N) {
    int i, j, iter;
    double sum, dx;

    for (iter = 0; iter < MAX_ITER; iter++) {
        dx = 0.0;
        for (i = 0; i < N; i++) {
            sum = 0.0;
            for (j = 0; j < N; j++) {
                if (i != j) {
                    sum += A[i][j] * X[j];
                }
            }
            double new_x = (B[i] - sum) / A[i][i];
            dx += fabs(new_x - X[i]);
            X[i] = new_x;
        }

        // Проверка на сходимость
        if (dx < EPSILON) {
            printf("Метод Зейделя сошелся за %d итераций.\n", iter + 1);
            return;
        }
    }

    printf("Метод Зейделя не сошелся за %d итераций.\n", MAX_ITER);
}

int main() {
    double** A;
    double* B;
    double* X;
    int N;

    // Чтение матрицы и вектора из файла
    readMatrixFromFile("input.txt", &A, &B, &N);

    // Выделение памяти для начального приближения X
    X = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        X[i] = 0.0;  // Начальное приближение
    }

    // Решение системы методом Зейделя
    seidel(A, B, X, N);

    // Вывод решения
    printf("Решение:\n");
    for (int i = 0; i < N; i++) {
        printf("X[%d] = %lf\n", i, X[i]);
    }

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(X);

    return 0;
}