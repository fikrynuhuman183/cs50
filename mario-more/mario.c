#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = 0;
    while (h <= 0 || h > 8)
    {
        h=get_int("Height :");
    }
    int n=1;
    do
    {
        for(int y=0; y<h-n;y++)
        {
            printf(" ");
        }
        for(int y=1; y<=n; y++)
        {
            printf("#");
        }
        printf("  ");\
        for(int y=1; y<=n; y++)
        {
            printf("#");
        }
        printf("\n");

        n++;
    }while(n<=h);


}