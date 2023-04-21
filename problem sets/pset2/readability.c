#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
int calculate_letters(string n);
int calculate_words(string n);
int calculate_sentences(string n);

int main(void)
{
    //need to round off index and use words as float
    string n = get_string("Text: ");
    int letters = calculate_letters(n);
    float words = calculate_words(n);
    int sentences = calculate_sentences(n);
    float L = (letters/words)*100;
    float S = (sentences/words)*100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("letters %i,words %f,sentences %i,L %f,S %f,index %i\n",letters,words,sentences,L,S,index);
    if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n",index);
    }

}

int calculate_letters(string n)
{
    int k = 0;
    int j = strlen(n);
    for(int i = 0;i < j;i++)
    {
        if((n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'A' && n[i] <= 'Z'))
        {
            k++;
        }
    }
    return k;
}
int calculate_words(string n)
{
    int k = 0;
    int j = strlen(n);
    for(int i = 0;i < j;i++)
    {
        if(n[i] == 32)
        {
            k++;
        }
    }
    return k + 1;
}
int calculate_sentences(string n)
{
    int k = 0;
    int j = strlen(n);
    for(int i = 0;i < j;i++)
    {
        if(n[i] == 33 || n[i] == 46 || n[i] == 63)
        {
            k++;
        }
    }
    return k;
}