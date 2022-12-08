#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encode(string key, string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You Must input only one command line argument\n");
        return 1;
    }
    string key = argv[1];
    for (int x = 0; x < 26; x++)
    {
        key[x] = tolower(key[x]);
    }
    bool letters[26];
    if (strlen(key) != 26)
    {
        printf("Invalid Key\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z')))
        {
            return 1;
        }
        if (letters[key[i] - 97])
        {
            return 1;
        }
        else
        {
            letters[key[i] - 97] = true;
        }
    }
    string plain_text = get_string("plaintext: ");
    encode(key, plain_text);
    return 0;
}


void encode(string key, string text)
{
    char output[1000];
    int num_key[26];
    for (int x = 0; x < 26; x++)
    {
        num_key[x] = key[x] - (97 + x);
    }
    for (int i = 'a'; i <= 'z'; i++)
    {
        for (int s = 0; s < strlen(text); s++)
        {
            if (text[s] == i && (text[s] >= 'a' && text[s] <= 'z'))
            {
                output[s] = i + num_key[i - 97];
            }
            else if (text[s] >= 32 && text[s] <= 64)
            {
                output[s] = text[s];
            }
        }
    }
    for (int i = 'A'; i <= 'Z'; i++)
    {
        for (int s = 0; s < strlen(text); s++)
        {
            if (text[s] == i && (text[s] >= 'A' && text[s] <= 'Z'))
            {
                output[s] = i + num_key[i - 'A'];
            }
        }
    }
    printf("ciphertext: %s\n", output);
}