#include <stdio.h>
#include <math.h>

#define POPULATION 2798170   // Население Новосибирской области
#define DAYS 90
#define DT 0.1  // Шаг времени для метода Эйлера

int main() {
    // Параметры модели из таблицы 11 для SEIR-D
    const double alpha_E = 0.999;/*Параметр заражения между бессимптомной и восприимчивой
    группами населения ( E 
   I)*/
    const double alpha_I = 0.999;/* Параметр заражения между инфицированным и восприимчивым
    населением, который связан с контагиозностью вируса
    и социальными факторами*/
    const double kappa = 0.042;/*Частота появления симптомов в открытых случаях, что приводит
    к переходу от бессимптомной к инфицированной популяции*/
    const double rho = 0.952; /*Скорость восстановления выявленных случаев (случаи, которые
    выявлены, но выздоравливают без каких-либо симптомов)*/
    const double beta = 0.999;/*Скорость выздоровления зараженных случаев*/
    const double mu = 0.0188;/* Смертность в результате COVID-19*/
    const double gama = 0.0;/*Скорость повторного заражения. Этот параметр является обратной
    величиной уровня иммунитета вируса */
    const double c_isol = 0.0;/* Коэффициент влияния индекса самоизоляции на заражаемость*/
    const double tau = 0.0;/*Латентный период (характеризует запаздывание выделения
    вирионов или заразности)*/

    // Начальные условия
    double S = POPULATION - 99 - 24;//восприимчивые
    double E = 99; //зараженные или находящиеся в инкубационном периоде индивидуумы;
    double I = 0;//инфицированные
    double R = 24;//выздоровевшие
    double D = 0;//умершие

    // Временные переменные для производных
    double dS, dE, dI, dR, dD;
    double c, N = POPULATION;

    // Улучшенный заголовок таблицы
    printf("Day\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n",
           "S", "E", "I", "R", "D" );
    printf("----------------------------------------------------------------------------\n");
    
    for (int day = 0; day <= DAYS; day++) {
        // Выводим результаты каждый день
       
        printf("%-3d\t%-10.2f\t%-10.2f\t%-10.2f\t%-10.2f\t%-10.2f\n", 
                   day, S, E, I, R, D);
        
        
        // Делаем шаги метода Эйлера в течение одного дня
        double t = day;
        for (double step = 0; step < 1.0; step += DT) {
            // Функция ограничения передвижения
            c = 1.0 + c_isol * (1.0 - 2.0/5.0 * 0.0);
            
            // Вычисляем производные
            dS = -c * (alpha_I * S * I / N + alpha_E * S * E / N) + gama * R;
            dE = c * (alpha_I * S * I / N + alpha_E * S * E / N) - (kappa + rho) * E;
            dI = kappa * E - beta * I - mu * I;
            dR = beta * I + rho * E - gama * R;
            dD = mu * I;
            
            // Делаем шаг метода Эйлера
            S += dS * DT;
            E += dE * DT;
            I += dI * DT;
            R += dR * DT;
            D += dD * DT;
        }
    }
    
    return 0;
}