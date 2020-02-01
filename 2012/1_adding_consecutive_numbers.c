#include <stdio.h>
#include <stdlib.h>

void print_consecutive_numbers(int i, int j)
{
    while(i < j) {
        printf("%d ", i);
        i++;
    }
    printf("%d\n", i);
    return;
}

int main(void) 
{
    int n;
    scanf("%d", &n);

    int sum, found = 0;
    /* 陷阱：注意审题，i 从 1 开始; 注意 15/2=7 要用 <= */
    for(int i=1; i<=n/2; i++) {
        for(int j=i+1; j<=n/2 + 1; j++) {
            /* NOTE 连续整数求和公式 */
            sum = (i+j)*(j-i+1)/2;
            if(sum == n) {
                print_consecutive_numbers(i, j);
                found = 1;
                break;
            }
            if(sum > n) 
                break;
        }
    }
    if(!found)
        puts("NONE");

    return EXIT_SUCCESS;
}
