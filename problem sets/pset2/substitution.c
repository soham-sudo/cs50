#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>

int check_key(string s);
//need to check lenght =26
//alphabets only
//no duplicates(hardest)
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage ./substitution key.\n");
        return 1;
    }
    if(check_key(argv[1]) == 2)
    {
        printf("Key should contain only alphabets.\n");
        return 1;
    }
    if(check_key(argv[1]) == 3)
    {
        printf("Key should contain 26 characters.\n");
        return 1;
    }
    if(check_key(argv[1]) == 4)
    {
        printf("Key should not contain dublicate characters.\n");
        return 1;
    }

    string n = get_string("plaintext:  ");
    printf("ciphertext: ");
    int m =strlen(n);

    //s is going to store the cipher text
    string s = argv[1];

    //a-z = 97-122 A-Z = 65-90
    for (int i = 0; i < m; i++)
    {
        //returns non zero if lower
        if (islower(n[i]) != 0)
        {
            int c = n[i] - 97;
            printf("%c", tolower(s[c]));
        }
        else if(isupper(n[i]) != 0)
        {
            int c = n[i] - 65;
            printf("%c", toupper(s[c]));
        }
        else
        {
            printf("%c", n[i]);
        }
    }
    printf("\n");
    return 0;
}

int check_key(string s)
{
    int n = strlen(s);
    int m =0;
    //cannot get argc value outside main
    //if(argc != 2)
    //{
        //return 1;
    //}
    for(int i = 0; i < n; i++)
    {
        if(isalpha(s[i]) != 0)
        {
            m++;
        }
        //check for duplicate
        for(int j =i + 1; j < n; j++)
        {
            if(s[i] == s[j])
            {
                return 4;
            }
        }
    }
    if (m != n)
    {
        return 2;
    }
    else if (m == n && n != 26)
    {
        return 3;
    }
    return 0;
}