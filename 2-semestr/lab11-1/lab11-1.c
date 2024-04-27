#include <stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#define E 0.001

double arccos(int n,double x)
{
    if (fabs(x)<=1)
    {
        double result= M_PI_2 -((2*n)/(pow(2,2*n)*pow(n,2))*(pow(x,2*n+1)/(2*n+1)));


        if (fabs(result) < E)
        {
            return 0;
        }
    return result + arccos(n+1, x);

    }
    return 0;
}

int main()
{
   double x = 0.5;
   int n =10;
   printf("arccos(%f) = %f\n", x, arccos(n,x));
   printf("arccos %f",acos(x));
    return 0;
}
