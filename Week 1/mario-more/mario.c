#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (int i = 1; i <= n; i++)
    {
        for (int s = 0; s < n; s++)
        {
            if (s >= n - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
// 0123  01234
//    #  #         0
//   ##  ##        1
//  ###  ###       2
// ####  ####      3