#include <stdio.h>

#define N 10000

int del(int a[], int n);
int bubble_sort(int a[], int n);
int locate(int a[], int b, int n);

int main()
{
    int a[N], b[N], n, num, z;
    while(scanf("%d", &n) != EOF) {
        for(int i=0; i<n; i++) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        bubble_sort(a, n);
        num = del(a, n);
        for(z=0; z<n-1; z++)
            printf("%d ", locate(a, b[z], num));
        printf("%d\n", locate(a, b[n-1], num));
    }

    return 0;
}

int del(int a[], int n)
{
    int i, j, k;
    for(i=0, j=i+1; j<n; j++) { /* 遇到连续相等元素，j后移，i不动 */
        if(a[i] != a[j]) {
            if((k=j-i-1) != 0)
                while(j<n) {
                    a[j-k] = a[j];
                    j++;
                }
            i++;
            j = i;
            n -= k;
        }
    }
    if(a[n-2] == a[n-1])
        n--;
    return n;
}

int bubble_sort(int a[], int n)
{
    int i,j,temp;
    for(i=0; i<n; i++) {
        for(j=i; j<n; j++) {
            if(a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    return 0;
}

int locate(int a[], int b, int n)
{
    int i,k;
    for(i=0; i<n; i++)
        if(a[i] == b)
            return i+1;
}
