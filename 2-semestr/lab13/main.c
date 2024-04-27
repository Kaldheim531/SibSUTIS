#include "functions.h"
#include <time.h>
// для сборки:
// mkdir build
// cd build
// cmake ..
// make
// cmake сгенерит Makefile'ы, а командой make соберется весь проект.

int main()
{

    int n;
    int C = 0, M = 0;

    printf("Введите размер массива n: ");
    // Используем цикл для надежного ввода n
    while (scanf("%d", &n) != 1 || n <= 0)
    { // Проверяем, что введенное значение - положительное число
        while (getchar() != '\n')
            ; // Очищаем буфер ввода
        printf("Ошибка: n должно быть целым положительным числом.\nВведите размер массива n: ");
    }

    int arr[n];

    int choiceForm;
    printf("Выберите способ формирования массива (1 - случайные числа , 2 - вручную): \n");
    scanf("%d", &choiceForm);


    int choiceType;
    printf("Выберите тип входных данных  (1 - случайный массив, 2 - упорядоченный массив  по убыванию, 3 - упорядоченный массив  по возрастание): ");
    scanf("%d", &choiceType);

      switch (choiceForm)
    {
    case 1:
        generateRandomArray(arr, n, choiceType);
        break;
    case 2:
        generateArray(arr, n,choiceType);
        break;
    case 3:
        printf("Неверный выбор сортировки!\n");
        break;
    default:
        printf("Неверный выбор сортировки!\n");
        return -1;
        break;
    }
    


    printf("Исходный массив:\n");
    printArray(arr, n);

    printf("Выберите метод сортировки (1 - heapsort, 2 -selectionsort, 3 - bubblesort.): ");
     int sortChoice;
    scanf("%d", &sortChoice);

    switch (sortChoice)
    {
    case 1:
        heapsort(arr, n, &C, &M);
        break;
    case 2:
        selectionsort(arr, n, &C, &M);
        break;
    case 3:
        bubblesort(arr, n, &C, &M);
        break;
    default:
        printf("Неверный выбор сортировки!\n");
        return -1;
        break;
    }
    
    printf("Отсортированный массив:\n");
    printArray(arr, n);

    printf("Количество сравнений C : %d\nКоличество M перестановок: %d\nC+M : %d\n", C, M,C+M);

    return 0;
}
