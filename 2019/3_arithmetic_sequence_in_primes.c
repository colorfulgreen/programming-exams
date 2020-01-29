/* 输入a、b，求 [a,b] 范围内的素数，及这些素数中的等差数列 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gen_composite_mask(int a, int b, int *mask)
{
    int i, j, ij;

    for(i=2; i<b; i++) {
        if(b/i < i)
            continue;
        for(j=i; i<b; j++) {
            ij = i*j;
            if(ij < a)
                continue;
            if(ij > b)
                break;
            mask[ij - a] = 1;
        }
    }
}

/* 发现等差数列 */
void find_arithmetic_sequence(int a, int b, int *mask)
{
    int diff, i, len = b - a + 1;
    for(diff=1; diff<floor(len/2); diff++) {
        for(int i = 0; i < diff; i++) {
            for(int j = i; j < len - diff*2; j += diff) {
                if(mask[j] == 0 && mask[j+diff] == 0 && mask[j+diff*2] == 0) {
                    printf("%d %d %d ", a+j, a+j+diff, a+j+diff*2);
                    j += diff*3;
                    while(j < len && mask[j] == 0) {
                        printf("%d ", a+j);
                        j += diff;
                    }
                    printf("\n");
                }
            }
        }
    }
}

int main(void)
{
    int a,b;
    scanf("%d %d", &a, &b);
    int len = b - a + 1;
    int *mask = malloc(len * sizeof(int));
    for(int i=0; i<len; i++)
        mask[i] = 0;
    gen_composite_mask(a, b, mask);
    find_arithmetic_sequence(a, b, mask);

    return EXIT_SUCCESS;
}
