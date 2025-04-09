#include <stdio.h>
#include <math.h>

#define epsilon 0.01

double f(double x) {
    return exp(-x * x);
}

double integrate_with_N(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.0;
    printf("  x        F(x)      F(x)*h\n");
    printf("---------------------------\n");
    for (int i = 0; i < N; i++) {
        double x = a + (i + 0.5) * h;
        double fx = f(x);
        double fx_h = fx * h;
        sum += fx;
        printf("%6.6lf  %8.6lf  %8.6lf\n", x, fx, fx_h); // Фиксированная ширина столбцов
    }
    printf("---------------------------\n");
    return sum * h;
}

double integrate_with_epsilon(double a, double b) {
    int N = 1; 
    double I_prev, I_current = integrate_with_N(a, b, N);

    do {
        N *= 2;
        I_prev = I_current;
        I_current = integrate_with_N(a, b, N);
    } while (fabs(I_current - I_prev) > epsilon);

    printf("\nИспользованное количество разбиений: %d\n", N);
    return I_current;
}

int main() {
    double a, b, S;

    printf("Введите a: ");
    scanf("%lf", &a);
    printf("Введите b: ");
    scanf("%lf", &b);
    
    S = integrate_with_epsilon(a, b);

    printf("Значение интеграла: %.15lf\n", S);

    return 0;
}