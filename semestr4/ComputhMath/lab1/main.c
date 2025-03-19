#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для чтения матрицы из файла
void read_matrix_from_file(double **a, double *b, int n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf", &a[i][j]);
        }
        fscanf(file, "%lf", &b[i]);
    }
    fclose(file);
}

// Функция для вывода матрицы
void print_matrix(double **a, double *b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%7.2f ", a[i][j]);
        }
        printf("| %7.2f\n", b[i]);
    }
    printf("\n");
}

// Функция для вычисления определителя матрицы
double determinant(double **a, int n) {
    if (n == 1) return a[0][0];
    double det = 0;
    double **submatrix = (double **)malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; i++) {
        submatrix[i] = (double *)malloc((n - 1) * sizeof(double));
    }

    for (int col = 0; col < n; col++) {
        for (int i = 1; i < n; i++) {
            int sub_i = i - 1;
            for (int j = 0; j < n; j++) {
                if (j != col) {
                    submatrix[sub_i][j < col ? j : j - 1] = a[i][j];
                }
            }
        }
        det += pow(-1, col) * a[0][col] * determinant(submatrix, n - 1);
    }

    for (int i = 0; i < n - 1; i++) free(submatrix[i]);
    free(submatrix);

    return det;
}

// Метод Гаусса
void gauss_method(double **a, double *b, double *x, int n) {
    int i, j, k;
    double c;

    // Прямой ход
    for (k = 0; k < n; k++) {
        printf("Шаг %d:\n", k + 1);
        print_matrix(a, b, n);

        // Проверка на вырожденность
        if (fabs(a[k][k]) < 1e-9) {
            printf("Ошибка: матрица вырождена.\n");
            return;
        }

        // Нормализация строки
        c = 1 / a[k][k];
        for (i = k; i < n; i++) {
            a[k][i] *= c;
        }
        b[k] *= c;

        // Обнуление элементов ниже главной диагонали
        for (i = k + 1; i < n; i++) {
            c = a[i][k];
            for (j = k; j < n; j++) {
                a[i][j] -= c * a[k][j];
            }
            b[i] -= c * b[k];
        }
    }

    // Обратный ход
    for (i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
    }
}

int main() {
    int n;
    printf("Введите размерность матрицы (n): ");
    scanf("%d", &n);

    
    double **a = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        a[i] = (double *)malloc(n * sizeof(double));
    }
    double *b = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));

    
    const char *filename = "input.txt";
    read_matrix_from_file(a, b, n, filename);

    printf("Исходная система:\n");
    print_matrix(a, b, n);

    
    double det = determinant(a, n);
    if (fabs(det) < 1e-9) {
        printf("Ошибка: матрица вырождена (определитель = %.2e).\n", det);
        return 1;
    }
    printf("Определитель матрицы: %.2e\n", det);

   
    gauss_method(a, b, x, n);

    
    printf("Решение системы:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.4f\n", i, x[i]);
    }

   
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
    free(b);
    free(x);

    return 0;
}