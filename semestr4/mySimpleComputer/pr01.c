#include "mySimpleComputer.h"
#include <stdio.h>

int main() {
    // Инициализация
    sc_memoryInit();
    sc_accumulatorInit();
    sc_icounterInit();
    sc_regInit();

    // Установка значений в память
    for (int i = 0; i < 10; i++) {
        sc_memorySet(i, i + 1);
    }

    // Вывод содержимого памяти
    printf("Memory contents:\n");
    for (int i = 0; i < 10; i++) {
        printCell(i);
    }

    // Попытка установить недопустимое значение в память
    int result = sc_memorySet(150, 100);
    printf("Attempt to set invalid memory address: %s\n", result == -1 ? "Failed" : "Success");

    // Установка флагов
    sc_regSet(FLAG_OVERFLOW, 1);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    printFlags();

    // Попытка установить некорректный флаг
    result = sc_regSet(0x20, 1);
    printf("Attempt to set invalid flag: %s\n", result == -1 ? "Failed" : "Success");

    // Установка значения аккумулятора
    sc_accumulatorSet(123);
    printAccumulator();

    // Попытка установить недопустимое значение аккумулятора
    result = sc_accumulatorSet(-1);
    printf("Attempt to set invalid accumulator value: %s\n", result == -1 ? "Failed" : "Success");

    // Установка значения счетчика команд
    sc_icounterSet(10);
    printCounters();

    // Попытка установить недопустимое значение счетчика команд
    result = sc_icounterSet(150);
    printf("Attempt to set invalid instruction counter value: %s\n", result == -1 ? "Failed" : "Success");

    // Декодирование значения ячейки памяти
    int value;
    sc_memoryGet(5, &value);
    printDecodedCommand(value);

    // Кодирование команды
    int encoded_value;
    sc_commandEncode(0, 0x10, 0x20, &encoded_value);
    printDecodedCommand(encoded_value);

    return 0;
}