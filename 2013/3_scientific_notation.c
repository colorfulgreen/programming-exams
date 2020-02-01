#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(void) {
    /* 理解题意：把输入当作字符串处理，绕过浮点数存储位数限制 */
    char *value = malloc(sizeof(char) * 100);
    int power, len, i;
    scanf("%s", value);
    len = strlen(value);

    /* 分情况处理 */
    if(len < 1)
        return EXIT_FAILURE;
    if(len == 1) {
        printf("%se0", value);
        return EXIT_SUCCESS;
    }

    if(value[0] == '0' && value[1] == '.') {
        for(i=2; i<len && value[i] == '0'; i++)
            ;
        power = -(i-1);
        putchar(value[i]);
        if(i+1<len)
            putchar('.');
        for(i=i+1; i<len; i++)
            putchar(value[i]);
        printf("e%d", power);
    }
    else {
        power = len - 1;
        putchar(value[0]);
        putchar('.');
        for(i=1; i<len; i++) {
            if(value[i] != '.')
                putchar(value[i]);
            else
                power = i - 1; 
        }
        printf("e%d", power);
    }

    return EXIT_SUCCESS;
}
