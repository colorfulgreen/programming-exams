/* 判断是否为合法的出栈顺序：直接用堆栈模拟进出栈 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int stack[SIZE];
int stack_index=0;

void push(int v) {
    stack[stack_index++] = v;
}

int is_empty(void) {
    return stack_index == 0;
}

int top(void) {
    if(!is_empty())
        return stack[stack_index - 1];
    return -1;
}

void pop()
{
    if(!is_empty()) {
        stack_index--;
    }
}

/*******/

int main(void)
{
    int n;
    int in[SIZE], out[SIZE];
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &in[i]);
    for(int i=0; i<n; i++)
        scanf("%d", &out[i]);

    /* 模拟进栈和出栈 */
    int i=0, j=0;
    while(i<n) {
        push(in[i++]);
        while(!is_empty() && out[j] == top()) {
            pop();
            j++;
        }
    }
    if(i==n && j==n)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
