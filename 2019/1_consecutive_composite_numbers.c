/* 输出 1 到 max 间的最长连续合数 
 * 思路：先写出小于 max 的所有素数
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 返回小于 max 的素数列表 */
int find_primes(int max, int *primes)
{
    if(max <= 1)
        return 0;

    int initial[4] = {2,3,5,7};
    int index, i, j;

    for(index=0; index<4; index++){
        primes[index] = initial[index];
    }
   
    for(i=2; i<=max; i++){
        for(j=0; j<index; j++) {
            if(i % primes[j] == 0)
                break;
        }
        if(j == index) {
            primes[index++] = i;
        }
    }
    return index;
}

void consecutive_composite_numbers(int max)
{
    if(max <= 3)
        return;

    int prime_factor_ceil = ceil(sqrt(max));
    /* TODO 内存管理 */
    int *primes = malloc(sizeof(int) * max);
    int prime_count;
    int prev, next, longest = 0, delta = 0;
    prime_count = find_primes(max, primes);
    for(int i=0; i<prime_count-1; i++) {
        delta = primes[i+1] - primes[i];
        if(delta > longest) {
            prev = primes[i];
            next = primes[i+1];
            longest = next - prev;
        }
    }
    for(int i=prev+1; i<next; i++)
        printf("%d ", i);
    printf("\n");
}

int main(void) {
    int max;
    while((scanf("%d", &max) == 1) && max > 0) {
        consecutive_composite_numbers(max); 
    }
    return EXIT_SUCCESS;
}
