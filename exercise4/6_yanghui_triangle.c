#include <stdio.h>
#include <stdlib.h>

int get_num(int i, int j)
{
    if(i == 0 || j == 0 || i == j)
        return 1;
    return get_num(i-1, j-1) + get_num(i-1, j);
}

int main(void)
{
    int n;
    scanf("%d", &n);

    for(int i=0; i<=n; i++) {
        for(int j=0; j<n-i; j++)
            printf("  ");
        for(int j=0; j<=i; j++)
            printf("%4d", get_num(i, j));
        putchar('\n');
    }

    return 0;
}
