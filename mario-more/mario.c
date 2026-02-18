#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    while (height <= 0)
    {
        height = get_int("height of pyramid: ");
    }
    for (int i = 0; i < height; i++)
    { // i is number of hashtags in the row
        for (int j = height - i; j > 1; j--)
        { // j is number of spaces in the row
            printf(" ");
        }
        for (int g = 0; g < 2; g++)
        {
            for (int k = i + 1; k > 0; k--)
            { // how many hashtags to place
                printf("#");
            }
            if (g == 0) {
                printf("  ");
            }
        }
        printf("\n");
    }
}
