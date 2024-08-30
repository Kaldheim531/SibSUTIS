#include <stdio.h>

void countingsort(int array[], int size)
{
    int output[size];
    int k = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > k)
        {
            k = array[i];
        }
    }

    int count[k + 1];
    for (int i = 0; i < k; ++i)
    {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        count[array[i]]++;
    }

    for (int i = 1; i <= k; i++)
    {
        count[i] += count[i - 1];
    }
    for (int i = 0; i < size; i++)
    {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }
    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }
}

int main()
{
    int array[] = {4, 5, 3, 4, 3, 2, 1};
    int size = 7;
    countingsort(array, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}