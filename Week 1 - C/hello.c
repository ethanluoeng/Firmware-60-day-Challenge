#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a + b;
}

int mult(int a, int b)
{
    return a*b;
}

void print_math(int (*op)(int, int), int x, int y)
{
    printf("%d\n", op(x, y));
}

int main(void) 
{
    print_math(add, 1, 2);
}