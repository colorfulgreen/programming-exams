#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[81], s2[81], out[81];
    int len1, len2;
    scanf("%s", s1);
    scanf("%s", s2);
    len1 = strlen(s1);
    len2 = strlen(s2);

    int p1, p2, carry = 0, mod, sum, index=0;
    for(p1=len1-1, p2=len2-1; p1>=0 && p2>=0; p1--, p2--) {
        sum = (s1[p1] - '0') + (s2[p2] - '0') + carry;
        mod = sum % 10;
        carry = (sum - mod) / 10;
        out[index++] = mod + '0';   /* 注意存储数字字符要 + '0' */
    }
    for(; p1>=0; p1--) {
        sum = (s1[p1] - '0') + carry;
        mod = sum % 10;
        carry = (sum - mod) / 10;
        out[index++] = mod + '0';
    }
    for(; p2>=0; p2--) {
        sum = (s2[p2] - '0') + carry;
        mod = sum % 10;
        carry = (sum - mod) / 10;
        out[index++] = mod + '0';
    }
    if(carry != 0)
        out[index++] = carry;

    int m, n, tmp;
    for(m=0, n=index-1; n > m; m++, n--) {
        tmp = out[m];
        out[m] = out[n];
        out[n] = tmp;
    }

    for(int i=0; i<index; i++)
        putchar(out[i]);
    putchar('\n');

    return 0;
}
