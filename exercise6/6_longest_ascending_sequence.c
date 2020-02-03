/* 最长升序子序列 - 动态规划 https://blog.csdn.net/u013309870/article/details/62037674
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10001

int main(void)
{
    char s[MAX_LEN];
    int f[MAX_LEN], len, i, j;
    scanf("%s", s);
    len = strlen(s);

    for(i=0; i<len; i++)
        f[i] = 1;

    for(i=0; i<len; i++) {
        for(j=0; j<i; j++) {
            if(s[i] >= s[j] && f[i] <= f[j]) {
                f[i] = f[j] + 1;
            }
        }
    }

    int max = 1;
    for(i=0; i<len; i++)
        if(f[i] > max)
            max = f[i];

    printf("%d\n", max);

    return EXIT_SUCCESS;
}
