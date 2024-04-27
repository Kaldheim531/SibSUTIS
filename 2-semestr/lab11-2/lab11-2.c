#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double AverageArif(int arr[], int size, int i, int count, double currentSum) 
{
    if (i == size) 
    {
        if (count == 0) 
        {
            return 0;
        } 
        else 
        {
            return  currentSum / count;
        }
    } 

    else 
    {
        if (arr[i] >= 3 && arr[i] <= 10) 
        {
            return AverageArif(arr, size, i + 1, count + 1, currentSum + arr[i]);
        } 
        else 
        {
            return AverageArif(arr, size, i + 1, count, currentSum);
        }
    }
}

int main()
{
    srand(time(NULL));
    int n=10;
    int A[n];
    for(int i=0;i<n;i++)
    {
        A[i]=rand()%10;
        printf("%d ",A[i]);
    }
     printf("\n ");
    printf("%f\n",AverageArif(A,n,0,0,0));
}
