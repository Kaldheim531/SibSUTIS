#include <stdio.h>
#include "mySimpleComputer.h"
#include "input_output.h"

int main() {
    // a. Инициализация
    sc_memoryInit();
    sc_accumulatorInit();
    sc_icounterInit();
    sc_regInit();

    // b. Установка значений в память и вывод
    sc_memorySet(0, 0x1234);
    sc_memorySet(1, 0x5678);
    sc_memorySet(2, 0x9ABC);
    sc_memorySet(3, 0xDEF0);
    sc_memorySet(4, 0x1111);
    sc_memorySet(5, 0x2222);
    sc_memorySet(6, 0x3333);
    sc_memorySet(7, 0x4444);
    sc_memorySet(8, 0x5555);
    sc_memorySet(9, 0x6666);

    printf("Memory contents:\n");
    for (int i = 0; i < 10; i++) {
        printCell(i);
    }

    // c. Попытка установить недопустимое значение в память
    int status = sc_memorySet(128, 0xFFFF);
    printf("Status of setting invalid memory address: %d\n", status);

    // d. Установка значений флагов и вывод
    sc_regSet(FLAG_OVERFLOW, 1);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    printFlags();

    // e. Попытка установить некорректное значение флага
    status = sc_regSet(0x20, 1);
    printf("Status of setting invalid flag: %d\n", status);

    // f. Установка значения аккумулятора и вывод
    sc_accumulatorSet(42);
    printAccumulator();

    // g. Попытка установить недопустимое значение аккумулятора
    status = sc_accumulatorSet(-1);
    printf("Status of setting invalid accumulator value: %d\n", status);

    // h. Установка значения счетчика команд и вывод
    sc_icounterSet(10);
    printCounters();

    // i. Попытка установить недопустимое значение счетчика команд
    status = sc_icounterSet(128);
    printf("Status of setting invalid instruction counter value: %d\n", status);

    // j. Декодирование значения ячейки памяти и аккумулятора
    int sign, command, operand;
    sc_commandDecode(0x1234, &sign, &command, &operand);
    printf("Decoded memory cell: sign=%d, command=%d, operand=%d\n", sign, command, operand);

    int accValue;
    sc_accumulatorGet(&accValue);
    printf("Decoded accumulator value: %d\n", accValue);

    // k. Кодирование команды и вывод в разных системах счисления
    int encodedValue;
    sc_commandEncode(1, 10, 20, &encodedValue);
    printDecodedCommand(encodedValue);

    return 0;
}