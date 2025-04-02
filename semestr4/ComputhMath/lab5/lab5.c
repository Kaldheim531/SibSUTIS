#include <stdio.h>
#include <math.h>
#define epsilon 0.01
double f(double x) {
    return exp(-x * x);
}

double integrate_with_N(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;

}

double integrate_with_epsilon(double a, double b) {

    int N = 1; // Начальное количество разбиений
    double I_prev, I_current = integrate_with_N(a, b, N);

    do {
        N *= 2;
        I_prev = I_current;
        I_current = integrate_with_N(a, b, N);
    } while (fabs(I_current - I_prev) > epsilon);

    printf("Использованное количество разбиений: %d\n", N);
    return I_current;

}


int main() {

    double a, b, S;

    printf("Введите  a: ");
    scanf("%lf", &a);
    printf("Введите  b: ");
    scanf("%lf", &b);
    

    S = integrate_with_epsilon(a, b);

    printf("Значение интеграла: %.15lf\n", S);

    return 0;

}