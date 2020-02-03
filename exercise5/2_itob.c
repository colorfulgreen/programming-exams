#include <stdio.h>
#include <stdlib.h>

void itob(int n, int b, char *s)
{
    int i = 0, j = 0, negtive = 0, mod, tmp;
    char ch;

    if(n == 0) {
        s[i++] = '0';
    }
    if(n < 0) {
        n = -n;
        negtive = 1;
    }
    while(n > 0) {
        mod = n % b;
        if(mod < 10)
            ch = mod + '0';
        else
            ch = mod + 'a' - 10;
        s[i++] = ch;
        n = (n - mod) / b;
    }
    s[i] = '\0';

    /* 反转 */
    for(i-=1; i>j; i--, j++) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}


int main(void)
{
    int n, b;
    char s[100];
    scanf("%d %d", &n, &b);
    itob(n, b, s);
    printf("%s\n", s);

    return EXIT_SUCCESS;
}
