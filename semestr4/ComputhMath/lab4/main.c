#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double newton_interpolation(double x_values[], double y_values[], int n, double x) {
    double table[n][n];
    
    for (int i = 0; i < n; i++) {
        table[i][0] = y_values[i];
    }
    
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            table[i][j] = (table[i+1][j-1] - table[i][j-1]) / (x_values[i+j] - x_values[i]);
        }
    }
    
    double result = table[0][0];
    double product_term = 1.0;
    
    for (int i = 1; i < n; i++) {
        product_term *= (x - x_values[i-1]);
        result += table[0][i] * product_term;
    }
    
    return result;
}
double Newton(double x, int n, double x_arr[], double y_arr[]){
    
    double sum = y_arr[0];
    for(int i = 1; i < n; ++i){
        
        double F = 0;
        for(int j = 0; j <= i; ++j){
            
            double den = 1;
            for(int k = 0; k <= i; ++k)
                if (k != j) 
                    den *= (x_arr[j] - x_arr[k]);

            F += y_arr[j]/den;
        }
        
        //äîìíîæàåì ðàçäåëåííóþ ðàçíîñòü íà ñêîáêè (x-x[0])...(x-x[i-1])
        for(int k = 0; k < i; ++k)
            F *= (x - x_arr[k]);
        sum += F;
    }
    return sum;
}
int main() {
    FILE *file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("Не удалось открыть файл in.txt\n");
        return 1;
    }
    
    double x_values[100], y_values[100];
    int n = 0;
    char line[256];
    
    // Чтение x значений
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
    
    // Чтение y значений
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
    
    if (m != n) {
        printf("Ошибка: количество x (%d) и y (%d) значений не совпадает\n", n, m);
        return 1;
    }
    
    if (n == 0) {
        printf("Ошибка: нет данных для интерполяции\n");
        return 1;
    }
    
    double x = 1.0;
    //double result = newton_interpolation(x_values, y_values, n, x);
    printf("\n");
  double result = Newton( x,n,x_values, y_values);
    printf("Значение полинома Ньютона N(1) = %.6f\n", result);
    
    return 0;
}