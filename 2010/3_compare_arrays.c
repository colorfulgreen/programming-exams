#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *a, int n)
{
    int i, j, tmp;
    for(i=1; i<n; i++) {
        tmp = a[i];
        for(j=i; j>0 && a[j-1] > tmp; j--)
            a[j] = a[j-1];
        a[j] = tmp;
    }
    return;
}

int main(void)
{
    int *a, *b, n, equal = 1;
    scanf("%d", &n);
    a = malloc(sizeof(int) * n);
    b = malloc(sizeof(int) * n);
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    for(int i=0; i<n; i++)
        scanf("%d", &b[i]);
    insertion_sort(a, n);
    insertion_sort(b, n);
    for(int i=0; i<n; i++) {
        if(a[i] != b[i]) {
            printf("not equal\n");
            equal = 0;
            break;
        }
    }
    if(equal)
        printf("equal\n");

    return EXIT_SUCCESS;
}
