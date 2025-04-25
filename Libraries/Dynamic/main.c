/* 
Compilation steps to create dynamic/shared library and binary

    rm *.o *.so
    gcc -fPIC -c add.c mul.c sub.c // compile position-independent code
    gcc -shared -o libarith.so add.o mul.o sub.o // Create shared library
    gcc main.c -L. -larith -o calculator_dynamic // link dynamically
    export LD_LIBRARY_PATH=.
    ./calculator_dynamic 

*/

#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);

int main() {
    int x, y;

    printf("Enter x value: ");
    scanf("%d", &x);

    printf("Enter y value: ");
    scanf("%d", &y);

    printf("Add: %d\n", add(x, y));
    printf("Sub: %d\n", sub(x, y));
    printf("Mul: %d\n", mul(x, y));

    return 0;
}