#include <stdio.h>

void print_space(int n);
void print_star(int n);
void print_first_last_line(int n);
void print_middle_line(int n);
void print_body(int n, int m);

int main(void)
{
    int i, n;
    scanf("%d", &n);
    print_first_last_line(n);

    for(int i=1; i<n; i++) 
        print_body(n, i);
    print_middle_line(n);
    for(i=n-2; i>0; i--)
        print_body(n,i);

    print_first_last_line(n);

    return 0;
}


void print_space(int n)
{
    for(int i=0; i<n; i++)
        putchar(' ');
}

void print_star(int n)
{
    for(int i=0; i<n; i++)
        putchar('*');
}

void print_first_last_line(int n) {
    print_space(n-1);
    print_star(n);
    print_space(n-1);
    putchar('\n');
}

void print_middle_line(int n)
{
    print_star(1);
    print_space(3*n - 4); /* TODO */
    print_star(1);
    putchar('\n');
}

void print_body(int n, int m)
{
    print_space(n-m-1);
    print_star(1);
    print_space(n+2*m-2);
    print_star(1);
    print_space(n-m-1);
    putchar('\n');
}
