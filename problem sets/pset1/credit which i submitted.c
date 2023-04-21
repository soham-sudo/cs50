#include <cs50.h>
#include <stdio.h>
int calculate_lenght(long n);
int lastalternate(long n);
int second_last_alternate(long n);
int firstdigit(long n);
int first2digit(long n);


int main(void)
{

    long n;
    do
    {
        n = get_long("Number : ");
    }
    while (n < 1);


    int lenght = calculate_lenght(n);
    int sum1 = lastalternate(n);
    int sum2 = second_last_alternate(n);
    int sum3 = (sum1 + sum2) % 10;

    if(sum3 != 0)
    {
        printf("INVALID\n");
    }

    if (sum3 == 0)
    {
        if (lenght == 15 && (first2digit(n) == 34 || first2digit(n) == 37))
        {
             printf("AMEX\n");
        }
        else if(lenght == 16 && (first2digit(n) >= 51 && first2digit(n) <= 55))
        {
             printf("MASTERCARD\n");
        }
        else if(firstdigit(n) == 4 && (lenght == 13 || lenght == 16))
        {
             printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }



}

int calculate_lenght(long n)
{
    int m = 0;
    while(n > 1)
    {
        n = n/10;
        m++;
    }return m;
}

int lastalternate(long n)
{
    int sum = 0;
    int lastdigit;
    while (n > 1)
    {
        lastdigit = n % 10;
        sum = lastdigit + sum;
        n = n / 100;
    }
    return sum;
}

int second_last_alternate(long n)
{
    n = n / 10;
    int sum = 0;
    int lastdigit;
    while (n > 1)
    {
        lastdigit = (n % 10)*2;

        if (lastdigit <= 9)
        {
            sum = lastdigit + sum;
        }
        else
        {
            sum = lastdigit % 10 + lastdigit / 10 + sum;
        }
        n = n / 100;
    }
    return sum;
}

int firstdigit(long n)
{

    while (n > 10)
    {
        n = n/10;
    }
    return n;
}

int first2digit(long n)
{
    while (n > 100)
    {
        n = n/10;
    }
    return n;
}
