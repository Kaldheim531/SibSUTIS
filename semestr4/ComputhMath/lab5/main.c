#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Подынтегральная функция
double f(double x) {
    return exp(-x * x);
}

// Функция вычисления интеграла методом центральных прямоугольников с заданным количеством разбиений
double integrate_with_N(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;
}

// Функция вычисления интеграла методом центральных прямоугольников с заданной погрешностью
double integrate_with_epsilon(double a, double b, double epsilon) {
    int N = 1; // Начальное количество разбиений
    double I_prev = 0.0;
    double I_current = integrate_with_N(a, b, N);

    do {
        N *= 2;
        I_prev = I_current;
        I_current = integrate_with_N(a, b, N);
    } while (fabs(I_current - I_prev) > epsilon);

    return I_current;
}

int main() {
    double a, b, epsilon, I;
    int N, choice;

    printf("Выберите режим работы:\n");
    printf("1 - Ввод количества разбиений N\n");
    printf("2 - Ввод погрешности epsilon\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    printf("Введите нижний предел интегрирования a: ");
    scanf("%lf", &a);
    printf("Введите верхний предел интегрирования b: ");
    scanf("%lf", &b);

    if (choice == 1) {
        printf("Введите количество разбиений N: ");
        scanf("%d", &N);
        I = integrate_with_N(a, b, N);
    } else if (choice == 2) {
        printf("Введите погрешность epsilon: ");
        scanf("%lf", &epsilon);
        I = integrate_with_epsilon(a, b, epsilon);
        printf("Использованное количество разбиений: %d\n", N);
    } else {
        printf("Неверный выбор.\n");
        return 1;
    }

    printf("Значение интеграла: %.15lf\n", I);

    return 0;
}