#include <stdio.h>
#include <math.h>
#include <locale.h>

// Функция для вычисления первой нормы матрицы
double firstNorm(double A[10][10], int n, int m) {
    int i, j;
    double sum = 0, subSum;
    for (i = 0; i < n; i++) {
        subSum = 0;
        for (j = 0; j < m; j++) {
            subSum += fabs(A[i][j]);
        }
        if (subSum > sum) {
            sum = subSum;
        }
    }
    return sum;
}

// Функция для вычисления второй нормы матрицы
double secondNorm(double A[10][10], int n, int m) {
    int i, j;
    double sum = 0, subSum;
    for (j = 0; j < n; j++) {
        subSum = 0;
        for (i = 0; i < m; i++) {
            subSum += fabs(A[i][j]);
        }
        if (subSum > sum) {
            sum = subSum;
        }
    }
    return sum;
}

// Функция для вычисления третьей нормы матрицы
double thirdNorm(double A[10][10], int n, int m) {
    int i, j;
    double sum = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum += A[i][j] * A[i][j];
        }
    }
    return sqrt(sum);
}

// Функция для округления числа
double okr(double X, double eps) {
    int i = 0;
    while (eps != 1) {
        i++;
        eps *= 10;
    }
    int okr = pow(10, i);
    X = (int)(X * okr + 0.5) / (double)okr;
    return X;
}

// Функция для решения системы методом Зейделя
void solveByZeidel(double A[10][10], double B[10], int N, double eps) {
    int k = 0, i, j;
    double X[10], s, g;

    // Инициализация начального приближения
    for (i = 0; i < N; i++) {
        X[i] = B[i];
    }

    do {
        s = 0;
        k++;

        for (i = 0; i < N; i++) {
            g = B[i];
            for (j = 0; j < N; j++) {
                g += A[i][j] * X[j];
            }
            s += (X[i] - g) * (X[i] - g);
            X[i] = g;
        }

    } while (sqrt(s) >= eps * (1 - thirdNorm(A, N, N)) / thirdNorm(A, N, N));

    // Вывод результатов
    printf("Решение системы:\n");
    for (i = 0; i < N; i++) {
        printf("X%d = %.6f\n", i, okr(X[i], eps));
    }
    printf("Число итераций: %d\n", k - 1);
    printf("Первая норма матрицы A: %.6f\n", firstNorm(A, N, N));
    printf("Вторая норма матрицы A: %.6f\n", secondNorm(A, N, N));
    printf("Третья норма матрицы A: %.6f\n", thirdNorm(A, N, N));
}

int main() {
    setlocale(LC_ALL, "Russian");

    double eps, A[10][10], B[10];
    int N, i, j;

    // Ввод размерности матрицы
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &N);

    // Ввод точности вычислений
    printf("Введите точность вычислений: ");
    scanf("%lf", &eps);

    // Ввод матрицы A
    printf("Заполните матрицу A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // Вывод матрицы A
    printf("\nВаша матрица A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }

    // Ввод столбца свободных членов B
    printf("\nЗаполните столбец свободных членов:\n");
    for (i = 0; i < N; i++) {
        printf("B[%d] = ", i + 1);
        scanf("%lf", &B[i]);
    }

    // Проверка условия сходимости
    if (thirdNorm(A, N, N) >= 1) {
        fprintf(stderr, "Условие сходимости по евклидовой метрике не выполняется!\n");
        return 1;
    }

    // Решение системы методом Зейделя
    solveByZeidel(A, B, N, eps);

    return 0;
}