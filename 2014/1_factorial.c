#include <stdio.h>
#include <stdlib.h>


int split_factorial(int n) 
{
    int split = n % 10;
    int accum = 0;

    if(n >= 10) {
        accum = split_factorial((n - split) / 10);
        printf("+%d!", split);
    }
    else {
        printf("%d!", split);
    }

    int fac = 1;
    while(split>1) {
        fac *= split;
        split--;
    }
    return accum + fac;
}


int main(void)
{
    int n, accum;
    accum = scanf("%d", &n);

    printf("%d,", n);
    accum = split_factorial(n);
    printf("=%d\n", accum);

    if(accum == n)
        printf("Yes\n");
    else
        printf("No\n");

    return EXIT_SUCCESS;
}
