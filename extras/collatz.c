#include <stdio.h>
#include <cs50.h>

int collatz(int n);
int steps = 0;

int main(void)
{
    int number = get_int("number\n");
    printf("%i\n", collatz(number));
}



int collatz(int n)
{

    if (n == 1)
    {
        return steps;
    }
    else if(n%2 == 0)
    {
        collatz(n/2);
        steps ++;
        return steps;

    }
    else
    {
        collatz(3*n+1);
        steps ++;
        return steps;
    }
}