#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int main() {
/*Проверить, является ли матрица A(n,n) диагональной (все элементы нули, кроме главной диагонали),
единичной (все элементы нули, на главной диагонали только единицы) или нулевой (все элементы нули).*/
int n;
printf("Величина квадратной матрицы = ");
scanf("%d",&n);

int A[n][n];
char flag_diagonal=0; // проверка на диагональность
char flag_edinich=0; // проверка на единичность
char flag_nul=0; // проверка на единичность
char flag=1; // подпадает ли матрица под какое то усливоие вообще


srand(time(NULL));


printf("\n");

//заполнение матрицы значениями с клавиатуры
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
       
        A[i][j]=rand()%2;
        //scanf("%d",&A[i][j]);
    }
     printf("\n");
}

//вывод матрциы
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        printf("%d ",A[i][j]);}
    printf("\n");}
    

printf("\n");

// проверка подпадает ли матрица под какое то усливоие вообще
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        // Проверяем, что элементы вне главной диагонали равны нулю
        if(i!=j && A[i][j]!=0)
            flag=0;
        }
    }

//если матрица соответствует какому то условию то определим его
if (flag==1){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            
            if(i==j && A[i][j]==1){ //проверка единичной матрицы
                flag_edinich=1;
            }
            
            
            if(i==j && A[i][j]!=0 && A[i][j]!=1){ //проверка диагональной матрицы
                flag_diagonal=1;
            }
            
            
            if(i==j && A[i][j]==0){ // проверка нулевой матрицы
                flag_nul=1;
            }
           
}
}
}


printf("flag %d\n",flag);   
printf("\n");      

if (flag==1){
    if (flag_nul==1) printf("Матрица Нулевая\n");
    else if (flag_edinich==1)  printf("Матрица Единичная\n");
    else if (flag_diagonal==1) printf("Матрица Диагональная\n");
}
else
printf("Матрицу нельзя классифицировать\n");

}