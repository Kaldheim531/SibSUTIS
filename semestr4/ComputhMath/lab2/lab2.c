#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.01  
#define MAX_ITER 1000  

void readMatrixFromFile(const char* filename, double*** A, double** B, int* N){
    FILE* file=fopen("input.txt","r");
    fscanf(file,"%d",N);

    *A = (double**)malloc((*N) * sizeof(double*));
    for (int i = 0; i < *N; i++) {
        (*A)[i] = (double*)malloc((*N) * sizeof(double));
    }
    *B = (double*)malloc((*N) * sizeof(double));
    
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            fscanf(file, "%lf", &(*A)[i][j]); 
        }
        fscanf(file, "%lf", &(*B)[i]);
    }

    fclose(file);
}


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
            printf("k%d X[%d] = %lf ",iter,i+1,X[i]);
        }
        puts("\n");

        
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

    
    readMatrixFromFile("input.txt", &A, &B, &N);

    
    X = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        X[i] = 0.0;  // Начальное приближение
    }


    seidel(A, B, X, N);

    
    printf("Решение:\n");
    for (int i = 0; i < N; i++) {
        printf("X[%d] = %lf\n", i, X[i]);
    }

    
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(X);

    return 0;
}

