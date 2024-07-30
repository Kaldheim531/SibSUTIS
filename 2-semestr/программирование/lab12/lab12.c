#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*Создайте структуру Вектор с элементами x, y, z – декартовые координаты.
Определить для M заданных векторов длину каждого вектора и найти номер самого длинного вектора.*/

struct vector
{
    int x;
    int y;
    int z;
};
int ThemostbiggestVector(struct vector)
{
    return  0;
}
int main()
{   
    srand(time(NULL));
    int M=3;
    struct vector number[M];
    for(int i=0;i<M;i++)
    {
        struct vector number[i]={rand()%5,rand()%5,rand()%5};
    }
    
     for(int i=0;i<M;i++)
    {
        printf("%d \n",number[i].x);
    }
    

}
