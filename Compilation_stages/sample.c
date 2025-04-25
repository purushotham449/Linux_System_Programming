/* Summary of Stages and Commands:

Stage                   | Command                               | Output
Preprocessing           | gcc -E sample.c -o sample.i             | .i file
Compilation             | gcc -S sample.i -o sample.s             | .s file
Assembly                | gcc -c sample.s -o sample.o             | .o file
Linking                 | gcc sample.o -o sample                  | executable

*/

#include <stdio.h>

int main()
{       
        printf("Hello World!!!!\n");
        return 0;
}
