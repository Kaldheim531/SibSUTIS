#include <stdio.h>
#include <math.h>

double f(double x) {
    return exp(-x * x);
}

double integrate_with_N(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.0;
    printf("x  F(x)  F(x)*h\n");
    for (int i = 0; i < N; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
        printf("%lf  %lf  %lf\n",x,f(x),f(x)*h);
    }

    return sum * h;
}




int main() {
    int N;
    double a, b,  S;

    printf("Введите  a: ");
    scanf("%lf", &a);
    printf("Введите  b: ");
    scanf("%lf", &b);
    printf("Введите  N: ");
    scanf("%d", &N);

    S = integrate_with_N(a, b, N);

    printf("Значение интеграла: %.15lf\n", S);

    return 0;

}