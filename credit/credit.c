#include <cs50.h>
#include <math.h>
#include <stdio.h>

void checksum(long c);

int main(void)
{
    long cardNum = get_long("Number: ");
    checksum(cardNum);
}

void checksum(long c)
{
    int n = 0;
    int j = 1;
    long k = 0;
    for (long i = 10; i < c * 10; i *= 10)
    {
        printf("i = %li\n", i); // test print of i
        if (j % 2 == 0)
        {
            int f = 2 * ((c % i) / (i / 10));
            if (f >= 10)
            {
                n += ((f % 10) + 1);
            }
            else
            {
                n += f;
            }
        }
        else
        {
            n += (c % i) / (i / 10);
        }
        j++;
        printf("j = %i\n", j); // test print of j
        printf("n = %i\n", n); // test print of n
        k = i;
    }
    int xx = c / (k / 100);
    printf("first two digits = %i\n", xx); // test print of xx
    if (n % 10 == 0)                       // if calculations work
    {
        if (xx / 10 == 4 && (j == 14 || j == 17))
        {
            printf("VISA\n");
        }
        else if ((xx == 34 || xx == 37) && (j == 16))
        {
            printf("AMEX\n");
        }
        else if ((xx == 51 || xx == 52 || xx == 53 || xx == 54 || xx == 55) && (j == 17))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
// test number: 4003600000000014
