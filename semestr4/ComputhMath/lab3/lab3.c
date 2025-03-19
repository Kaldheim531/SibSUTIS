#include <stdio.h>
#include <math.h>
#include <float.h>

#define EPSILON 0.000001  
#define MAX_ITER 100     


double f(double x) {
    return 2 * x * x - x * x * x - exp(x);  
}


double derivative(double (*f)(double), double x) {
    double h = EPSILON; 
    return (f(x + h) - f(x)) / h;
}

double second_derivative(double (*f)(double), double x) {
    double h = EPSILON; 
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

double locmann_method(double (*f)(double), double x0, double accuracity, int max_iter) {
    double x = x0;
    printf("| n  |     x      |    f(x)    |  |x_next-x||\n");
    for (int i = 0; i < max_iter; i++) {
        double fx = f(x);              
        double dfx = derivative(f, x);  
        double d2fx = second_derivative(f, x); 

        if (dfx == 0) {
            printf("Производная равна нулю. Метод не может быть продолжен.\n");
            return NAN;
        }

        
        double x_next = x - (2 * fx * dfx) / (2 * dfx * dfx - fx * d2fx);

        
        printf("| %2d | %10.6lf | %10.6lf | %10.6lf |\n", i, x, fx, fabs(x_next - x));
        
        
        if (fabs(x_next - x) < accuracity) {
            printf("\nКорень найден за %d итераций.\n", i + 1);
            return x_next;
        }

        x = x_next;
    }

    printf("Достигнуто максимальное количество итераций.\n");
    return NAN;
}

int main() {
    double x0 = -1.0;  
    double root = locmann_method(f, x0, EPSILON, MAX_ITER);
    
    if (!isnan(root)) {
        printf("Найденный корень: %lf\n", root);
    }

    return 0;
}