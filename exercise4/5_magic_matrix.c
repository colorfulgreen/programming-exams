#include <stdio.h>
#include <stdlib.h>

void print_line(int n, int i) 
{
    for(int j=1; j<=n; j++) 
        printf("%d", j < n - i ? j : n - i);
    for(int j=n-1; j>=1; j--) 
        printf("%d", j < n - i ? j : n - i);
    putchar('\n');

}

int main(void)
{
    int n;
    scanf("%d", &n);

    for(int i=n-1; i>=0; i--) 
        print_line(n, i);
    for(int i=1; i<=n-1; i++) 
        print_line(n, i);

    return 0;
}

