#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b);
void heapify(int arr[], int n, int i, int *c, int *m);
void heapsort(int arr[], int n, int *c, int *m);
void selectionsort(int arr[], int n, int *c, int *m);
void bubblesort(int arr[], int n, int *c, int *m);


void arrayrandom(int arr[], int n);
void arraysortedhigh(int arr[], int n);
void arraysortedlow(int arr[], int n);
void printArray(int *arr, int n);
void generateRandomArray(int *arr, int n, int mode);
void generateArray(int *arr, int n,int mode);

void readNumbersFromFile(int *arr,  int n);