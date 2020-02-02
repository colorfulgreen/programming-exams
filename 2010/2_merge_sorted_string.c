#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main(void)
{
    char *s1, *s2, prev = '\0';
    int len1, len2, pos1 = 0, pos2 = 0;
    s1 = malloc(sizeof(char) * BUFFER_SIZE);
    s2 = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(s1, BUFFER_SIZE, stdin);
    fgets(s2, BUFFER_SIZE, stdin);
    len1 = strlen(s1);
    len2 = strlen(s2);
    s1[len1-1] = '\0';
    s2[len2-1] = '\0';

    while(pos1 < len1 && pos2 < len2) {
        if(s1[pos1] <= s2[pos2]) {
            if(prev != s1[pos1]) {
                putchar(s1[pos1]);
                prev = s1[pos1];
            }
            pos1++;
        }
        else {
            if(prev != s2[pos2]) {
                putchar(s2[pos2]);
                prev = s2[pos2];
            }
            pos2++;
        }
    }
    while(pos1 < len1) {
        if(prev != s1[pos1]) {
            putchar(s1[pos1]);
            prev = s1[pos1];
        }
        pos1++;
    } 
    while(pos2 < len2) {
        if(prev != s2[pos2]) {
            putchar(s2[pos2]);
            prev = s2[pos2];
        }
        pos2++;
    }
    putchar('\n');

    return 0;
}
