#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
bool only_digits(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if(only_digits(argv[1]) == false)
    {
        printf("key should contain digits only\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string n = get_string("planitext:  ");

    //ci = (pi + k)%26 A-Z = 65-90 ,a-z = 97-122,0-9 = 48-57

    int length = strlen(n);

    printf("ciphertext: ");

    for (int i = 0; i < length; i++)
    {
        if (n[i] >= 'a' && n[i] <= 'z')
        {
            printf("%c", 97 + (n[i] - 97 + key) % 26);
        }
        else if (n[i] >= 'A' && n[i] <= 'Z')
        {
            printf("%c", 65 + (n[i] - 65 + key) % 26);
        }
        else
        {
            printf("%c", n[i]);
        }
    }
    printf("\n");
}
bool only_digits(string s)
{
    int n = strlen(s);
    //to check all keys are digits
    int m = 0;
    for(int i = 0; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            m++;
        }
    }
    if (m == n)
    {
        return true;
    }
    return false;
}