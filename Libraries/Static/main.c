/* 
Compilation steps to create static library and binary

    gcc -c add.c 
    gcc -c mul.c
    gcc -c main.c
    gcc main.o -L. -larith -o calculator
    ./calculator
    
*/

#include <stdio.h>

int add(int a, int b);
int mul(int a, int b);

int main() {
    int x, y;

    printf("Enter x value: ");
    scanf("%d", &x);

    printf("Enter y value: ");
    scanf("%d", &y);

    printf("Add: %d\n", add(x, y));
    printf("Mul: %d\n", mul(x, y));

    return 0;
}