#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

double newton_interpolation(double x_values[], double y_values[], int n, double x) {
    double table[n][n];
    for (int i = 0; i < n; i++) {
        table[i][0] = y_values[i];
    }
    
    // Вычисляем разделённые разности и выводим их
    printf("\nТаблица разделённых разностей:\n");
    for (int j = 1; j < n; j++) {
        printf("Разности %d-го порядка:\n", j);
        for (int i = 0; i < n - j; i++) {
            table[i][j] = (table[i+1][j-1] - table[i][j-1]) / (x_values[i+j] - x_values[i]);
            printf("f[x%d..x%d] = %f\n", i, i+j, table[i][j]);
        }
        printf("\n");
    }
    
    // Вычисляем значение полинома и выводим его вид
    printf("Итоговый интерполяционный многочлен Ньютона:\n");
    printf("N(x) = %f", table[0][0]);
    
    double result = table[0][0];
    double product_term = 1.0;
    
    for (int i = 1; i < n; i++) {
        product_term *= (x - x_values[i-1]);
        printf(" + %f", table[0][i]);
        for (int k = 0; k < i; k++) {
            printf("*(x - %f)", x_values[k]);
        }
        result += table[0][i] * product_term;
    }
    printf("\n");
    
    return result;
}

int main() {

    FILE *file = fopen("in.txt", "r");
    double x_values[100], y_values[100];
    
    int n = 0;
    char line[256];
    
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Ошибка чтения x значений\n");
        fclose(file);
        return 1;
    }
    
    char *token = strtok(line, " ");
    while (token != NULL && n < 100) {
        x_values[n] = atof(token);
        token = strtok(NULL, " ");
        n++;
    }
    
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Ошибка чтения y значений\n");
        fclose(file);
        return 1;
    }
    
    int m = 0;
    token = strtok(line, " ");
    while (token != NULL && m < n) {
        y_values[m] = atof(token);
        token = strtok(NULL, " ");
        m++;
    }
    
    fclose(file);
    
    
    
    double x = 1.0;
    //double result = newton_interpolation(x_values, y_values, n, x);
    printf("\n");
    double result = newton_interpolation(x_values, y_values, n, x);
    printf("Значение полинома Ньютона N(1) = %.6f\n", result);
    
    return 0;
}