#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE* ptr = fopen(argv[1], "r");
    FILE* ptr2 = fopen(argv[2], "w");
    FILE* ptr3 = fopen(argv[3], "w");
    char a[3];
    fread(a, 1, 3, ptr);
    fwrite(a, 1, 3, ptr2);
    char string[4];
    while (fread(string, 1, 4, ptr))
    {
        fwrite(string, 1, 4, ptr3);
    }
}