#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_sentences(string text);
int count_words(string text);
float readability(string text);

int main(void)
{
    string to_ev = get_string("Text: ");
    int read = readability(to_ev);
    if (read < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (read < 16)
    {
        printf("Grade %i\n", read);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

float readability(string text)
{
    float Words = count_words(text);
    float L = (count_letters(text) / Words) * 100; // average number of letters per 100 words
    float S = (count_sentences(text) / Words) * 100; // average number of sentences per 100 words
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f/%f/%f/%f", Words, L, S, index);
    int index_mult_ten = index * 10;
    if (index_mult_ten % 10 >= 5)
    {
        index++;
    }
    return index;
}

int count_letters(string text)
{
    int num = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (('a' <= text[i] && 'z' >= text[i]) || ('A' <= text[i] && 'Z' >= text[i]))
        {
            num++;
        }
    }
    return num;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if ((text[i] == 46) || (text[i] == 33) || (text[i] == 63))
        {
            sentences++;
        }
    }
    return sentences;
}
int count_words(string text)
{
    int words = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == 32)
        {
            words++;
        }
    }
    return words;
}