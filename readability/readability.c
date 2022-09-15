#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string s);
int count_words(string words);
int count_sentences(string sentences);


int main(void)
{
    string text = get_string("Text :");
    float L = (float)count_letters(text) / (float)count_words(text) * (float)100;
    float S = (float)count_sentences(text) / (float)count_words(text) * (float)100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
//count leters
int count_letters(string s)
{
    int length = strlen(s);
    int n_letters = 0;
    for (int i=0; i < length; i++)
    {
        if (isalpha(s[i]) != 0)
        {
            n_letters++;
        }
    }
    return n_letters;
}
//count words
int count_words(string words)
{
    int length = strlen(words);
    int n_words = 0;
    for (int i=0; i < length; i++)
    {
        if(isspace(words[i]) != 0)
        {
            n_words++;
        }
    }
    return n_words;
}
int count_sentences(string sentences)
{
    int length = strlen(sentences);
    int n_sentences = 0;
    for (int i=0; i < length; i++)
    {
        if(sentences[i] == 33 || sentences[i] == 63 || sentences[i] == 46)
        {
            n_sentences++;
        }
    }
    return n_sentences;
}