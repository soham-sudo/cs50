#include<stdio.h>
#include<cs50.h>
int lenght(int n);
int main (void)
{
    int n = get_int("Number : ");
    int m = lenght(n);
    int lastdigit;
    int sum = 0;
    while(n > 1)
    {
        lastdigit = n%10;
        sum =lastdigit + sum;
        n = n/10;
    }
    printf("lenght = %i and sum = %i\n",m,sum);
}

int lenght(int n)
{
    int m = 0;
    while(n > 1)
    {
        n = n/10;
        m++;
    }return m;
}