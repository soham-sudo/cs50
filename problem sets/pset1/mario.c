#include <cs50.h>
#include <stdio.h>


void pyramid(int n);
int main(void)
{
    int n;
    do
    {
        n = get_int("Height : ");
    }
    while( n < 1 || n > 8);

    {
        //pyramid function
        pyramid(n);
    }
}


void pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i+1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < i+1;k++)
        {
            printf("#");
        }
        printf("\n");
    }
}