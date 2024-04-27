#include "functions.h"

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i, int *c, int *m)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
    {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        (*m)++;
        heapify(arr, n, largest, c, m);
    }
    (*c)++;
}

void heapsort(int arr[], int n, int *c, int *m)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, c, m);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        (*m)++;
        heapify(arr, i, 0, c, m);
    }
}
void selectionsort(int arr[], int n, int *c, int *m)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
            (*c)++;
        }
        swap(&arr[minIndex], &arr[i]);
        (*m)++;
    }
}
void bubblesort(int arr[], int n, int *c, int *m)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                (*m)++; // увеличиваем количество перестановок
            }
            (*c)++; // увеличиваем количество сравнений
        }
    }
}
void arrayrandom(int *arr, int n)
{
    srand(time(NULL)); // Инициализация генерации случайных чисел
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 502 - 250; 
    }
}

void readNumbersFromFile(int *arr,  int n) {
    
    FILE* file = fopen("nubmers.txt", "r");

    // Чтение чисел из файла в массив
    int i = 0;
    while (fscanf(file, "%d", &n) == 1) {
        arr[i++] = n;
    }

    fclose(file);

    
}


void arraycreate(int *arr,int n){
    printf("Введите элементы массива:\n");
    for (int i = 0; i < n; i++) {
        printf("Элемент %d: ", i + 1);
        scanf("%d", &arr[i]); // Ввод элемента
    }
}

void arraysortedhigh(int *arr, int n)
{
    
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (arr[i] > arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    
}
void arraysortedlow(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
            for (int j = i + 1; j < n; j++)
            {
                if (arr[i] < arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
    }
    
}

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void generateRandomArray(int *arr, int n, int mode)
{
     if (mode==1 || mode==2 || mode==3){
    arrayrandom(arr, n);

    switch(mode){
        case 1:
        break;
        case 2:
        arraysortedlow(arr,  n);
        break;
        case 3:
        arraysortedhigh( arr,  n);
        break;
        default:
        printf("Неверный выбор сортировки! будет рандомная сортировка\n");
        
    }
     }
}

void generateArray(int *arr, int n, int mode) {
    if (mode==1 || mode==2 || mode==3){
    arraycreate(arr,n);
    switch(mode){
        case 1:
        break;
        case 2:
        arraysortedlow(arr,  n);
        break;
        case 3:
        arraysortedhigh( arr,  n);
        break;
        default:
        printf("Неверный выбор сортировки! будет рандомная сортировка\n");
        
    }
   } 
}

void generateArrayFromFile(int *arr, int n, int mode) {
     if (mode==1 || mode==2 || mode==3){
    readNumbersFromFile(arr,  n);

    switch(mode){
        case 1:
        break;
        case 2:
        arraysortedlow(arr,  n);
        break;
        case 3:
        arraysortedhigh( arr,  n);
        break;
        default:
        printf("Неверный выбор сортировки! будет рандомная сортировка\n");
        
    }
     }
}


