/* 输出 1 到 max 间的最长连续合数 
 * 思路：mask 数组标记所有的合数
 */

#include <stdio.h>
#include <stdlib.h>

void consecutive_composite_numbers(int n){
    int *mask = malloc((n+1) * sizeof(int));
    int i,j,index;

    /* TODO 内存初始化 */
    for(i=0; i<n+1; i++) {
        mask[i] = 0;
    }

    /* 标记合数 */
    for(i=2; i<n; i++) { /* 注意不能使用因子 1 */
        if(n / i < i)
            break;
        for(j=i; i<n; j++) { /* TODO 只用两个因子，可以覆盖全部的数？*/
            index = i*j;
            if(index > n) {
                break;
            }
            mask[index] = 1;
        }
    }

    /* 找出最长连续合数 */
    int cnt = 0;
    int max_cnt = 0;
    int max_index = -1;
    for(i=4; i<n; i++){
        if(mask[i] != 0)
            cnt++;
        else if(mask[i] == 0 && mask[i-1] != 0) {
            if(cnt > max_cnt) {
                max_cnt = cnt;
                max_index = i;
            }
            cnt = 0;
        }
    }
    if(cnt > max_cnt) { /* 考虑出现在尾部的特殊情况 */
        max_cnt = cnt + 1;
        max_index = n + 1;
    }

    if(max_cnt > 0){
        for(int i = max_index - max_cnt; i < max_index; i++)
            printf("%d ", i);
        printf("\n");
    }
}


int main(void)
{
    int max = 0;
    printf("input max integer:\n");
    if(scanf("%d", &max) == 1 && max > 0)
        consecutive_composite_numbers(max);
    
    return EXIT_SUCCESS;
}
