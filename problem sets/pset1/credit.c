#include <cs50.h>
#include <stdio.h>
int calculate_lenght(long n);
int lastalternate(long n);
int second_last_alternate(long n);
int firstdigit(long n);

int main(void)
{
    //cannot use "for loop" here
    //in do while you need to declare the "n" before
    // we need to make n constant too but cannot make n constant in while loop so make functions for various purposes.
    long n;
    do
    {
        n = get_long("credit card number : ");
    }
    while (n < 1);
    //last digit n%10
    // i think "int sum"  means it starts from zero ok to use when using while loop
    //when uisng do while "int sum = 0" to be used
    //second last digit n/10 then n%10

    int lenght = calculate_lenght(n);
    int sum1 = lastalternate(n);
    int sum2 = second_last_alternate(n);
    int sum3 = (sum1 + sum2)%10;
    int a = firstdigit(n);
    printf("sum3 = %i sum1 = %i sum2 = %i  %i\n",sum3,sum1,sum2,a);
    if(sum3 != 0 )
    {
        printf("INVALID\n");
    }
    if(sum3 == 0)
    {
        printf("card valid\n");
        if(lenght == 15)
        {
            printf("AMEX\n");
        }
        else if(lenght == 16 && firstdigit(n) == 5)
        {
            printf("MASTERCARD\n");
        }
        else if(firstdigit(n) == 4)
        {
            printf("VISA\n");
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
    while(n > 1)
    {
        lastdigit = n%10;
        sum = lastdigit + sum;
        n = n/100;
    }return sum;
}

int second_last_alternate(long n)
{
    n = n/10;
    int sum = 0;
    int lastdigit;
    while(n > 1)
    {
        lastdigit = (n%10)*2;

        if(lastdigit <= 9 )
        {
            sum = lastdigit + sum;
        }
        else
        {
            sum = lastdigit%10 + lastdigit/10 + sum;
        }
        n = n/100;
    }return sum;
}

int firstdigit(long n)
{

    while(n > 10)
    {
        n = n/10;
    }return n;
}
