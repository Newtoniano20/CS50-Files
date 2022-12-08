#include <cs50.h>
#include <stdio.h>
#include <math.h>

long int first_numbers(long int n);
int length(long int n);
bool checksum(long int n);

int main(void)
{
    long int card_number = get_long("Card Number: ");
    int n_len = length(card_number);
    long int two_fn = first_numbers(card_number);

    if (checksum(card_number) == false)
    {
        printf("INVALID\n");
    }
    else if (n_len == 15 && (two_fn == 34 || two_fn == 37))
    {
        printf("AMEX\n");
    }
    else if (n_len == 16 && (two_fn >= 51 && two_fn <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((n_len == 16 || n_len == 13) && (two_fn >= 40 && two_fn < 50))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checksum(long int n)
//
// Checks the checksum according to CS50's instructions
//
{
    long int num_len = length(n);
    int sum = 0, rem = 0;
    for (int i = 1; i < num_len; i++)
    {
        // Add odd number starting from the left to sum
        sum += (n % 10);
        // we move to the next number from the left
        n /= 10;
        // we add even number starting from the left mult by two
        rem = (n % 10) * 2;
        // if the result of the latter is greater than 10, we add the sum of the first and second digit of the latter
        if (rem < 10)
        {
            sum += rem;
        }
        else
        {
            sum += (rem / 10) + (rem % 10);
        }
        // we move to the next number
        n /= 10;
    }
    //printf("%i", sum);
    // checking if sum is valid (finishes with a 0)
    if ((sum % 10) == 0)
    {
        return true;
    }
    return false;
}


int length(long int n)
//
// Will return the length of a sequence of numbers
//
{
    int len = 0;
    while (n != 0)
    {
        n /= 10;
        len++;
    }
    return len;
}

long int first_numbers(long int n)
//
// Will return the two first numbers of a sequence
//
{
    long int num_len = length(n);
    long int first_num = n / (pow(10, (num_len - 2)));
    return first_num;
}