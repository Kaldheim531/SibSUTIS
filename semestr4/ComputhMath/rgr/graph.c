#include <stdio.h>
#include <math.h>

#define POPULATION 2798170
#define DAYS 90
#define DT 0.1

int main() {
    const double alpha_E = 0.999;
    const double alpha_I = 0.999;
    const double kappa = 0.042;
    const double rho = 0.952;
    const double beta = 0.999;
    const double mu = 0.0188;
    const double gama = 0.0;
    const double c_isol = 0.0;
    const double tau = 0.0;

    double S = POPULATION - 99 - 24;
    double E = 99;
    double I = 0;
    double R = 24;
    double D = 0;

    double dS, dE, dI, dR, dD;
    double c, N = POPULATION;

    // CSV файл
    FILE *fp = fopen("seird_data.csv", "w");
    fprintf(fp, "Day,S,E,I,R,D,N\n");

    for (int day = 0; day <= DAYS; day++) {
        fprintf(fp, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", 
                day, S, E, I, R, D, S + E + I + R + D);

        for (double step = 0; step < 1.0; step += DT) {
            c = 1.0 + c_isol * (1.0 - 2.0/5.0 * 0.0);

            dS = -c * (alpha_I * S * I / N + alpha_E * S * E / N) + gama * R;
            dE = c * (alpha_I * S * I / N + alpha_E * S * E / N) - (kappa + rho) * E;
            dI = kappa * E - beta * I - mu * I;
            dR = beta * I + rho * E - gama * R;
            dD = mu * I;

            S += dS * DT;
            E += dE * DT;
            I += dI * DT;
            R += dR * DT;
            D += dD * DT;
        }
    }

    fclose(fp);
    return 0;
}
