#include <stdio.h>
#include <stdlib.h>

/* 打印约数，返回约数和 */
int gen_divisors(int n) {
    int sum = 1;
    printf("1");

    /* NOTE 最大的约数不超过 n/2 */
    for(int i=2; i<=n/2; i++) { 
        if(n % i == 0) {
            printf("+%d", i);
            sum += n/i;
        }
    }
    printf("=%d\n", sum);
    return sum;
}


int main(void)
{
    int a, b;
    int sum_a = 0, sum_b = 0;
    scanf("%d %d", &a, &b);

    printf("%d,", a);
    sum_a = gen_divisors(a);
    printf("%d,", b);
    sum_b = gen_divisors(b);

    printf("%d\n", sum_a == b && sum_b == a ? 1 : 0);

    return EXIT_SUCCESS;
}
