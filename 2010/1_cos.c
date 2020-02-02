#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926

int factorial(int n)
{
    int result = 1;
    while(n>1) {
        result *= n;
        n--;
    }
    return result;
}

/* 泰勒展开 */
double cos(double x) 
{
    double result = 0;
    for(int n=0; n<5; n++)
    {
        result += pow(-1, n) * pow(x, 2*n) / factorial(2*n);
    }
    return result;
}

int main(void) {
    double x, result;
    scanf("%lf", &x); /* NOTE double 使用 %lf 格式化 */
    while(x > PI) 
        x -= 2*PI;
    while(x < -PI)
        x += 2*PI;
    result = cos(x);
    printf("%lf\n", result);
    return EXIT_SUCCESS;
}
