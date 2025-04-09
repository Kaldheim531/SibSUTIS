#include <stdio.h>


#define POPULATION 2798170   // Население Новосибирской области (примерно)
#define DAYS 90
#define DT 0.1  // Шаг времени для метода Эйлера

typedef struct {
    double S, E, I, R, D;
} State;

// Параметры модели из таблицы 11 для SEIR-D
const double alpha_E = 0.999;
const double alpha_I = 0.999;
const double kappa = 0.042;
const double rho = 0.952;
const double beta = 0.999;
const double mu = 0.0188;
const double gama = 0.0;  // Не указано в таблице, предположим 0
const double c_isol = 0.0;
const double tau = 0.0;    // Не указано в таблице, предположим 0

// Функция ограничения передвижения
double c_func(double t) {
    return 1.0 + c_isol * (1.0 - 2/5 * 0.0);  // Упрощенная версия, так как a(t) не определена
}

// Производные функции для модели SEIR-D
void derivatives(const State* current, State* derivs, double t) {
    double N = POPULATION;
    double c = c_func(t - tau);
    
    derivs->S = -c * (alpha_I * current->S * current->I / N + alpha_E * current->S * current->E / N) + gama * current->R;
    derivs->E = c * (alpha_I * current->S * current->I / N + alpha_E * current->S * current->E / N) - (kappa + rho) * current->E;
    derivs->I = kappa * current->E - beta * current->I - mu * current->I;
    derivs->R = beta * current->I + rho * current->E - gama * current->R;
    derivs->D = mu * current->I;
}

// Метод Эйлера для решения системы ОДУ
void euler_step(State* state, double t, double dt) {
    State derivs;
    derivatives(state, &derivs, t);
    
    state->S += derivs.S * dt;
    state->E += derivs.E * dt;
    state->I += derivs.I * dt;
    state->R += derivs.R * dt;
    state->D += derivs.D * dt;
}

int main() {
    State state;
    // Начальные условия из таблицы 11 для SEIR-D
    state.S = POPULATION - 99 - 24;  // S0 = N - E0 - R0 (D0 и I0 предположим 0)
    state.E = 99;
    state.I = 0;     // Не указано в таблице, предположим 0
    state.R = 24;
    state.D = 0;     // Не указано в таблице, предположим 0
    
    printf("Day\tS\t\tE\t\tI\t\tR\t\tD\t\tN\n");
    
    for (int day = 0; day <= DAYS; day++) {
        // Выводим результаты каждый день (пропускаем промежуточные шаги)
        if (day % 1 == 0) {
            printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", 
                   day, state.S, state.E, state.I, state.R, state.D,
                   state.S + state.E + state.I + state.R + state.D);
        }
        
        // Делаем шаги метода Эйлера в течение одного дня
        double t = day;
        for (double step = 0; step < 1.0; step += DT) {
            euler_step(&state, t + step, DT);
        }
    }
    
    return 0;
}