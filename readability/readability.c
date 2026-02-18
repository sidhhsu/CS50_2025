#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    int words = 0;
    int letters = 0;
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
        else if (isalpha(text[i]))
        {
            letters++;
        }
        else if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && isblank(text[i + 1]))
        {
            sentences++;
        }
    }
    words++; // to compensate for the last word
    sentences++;
    float L = (float) letters / (float) words * 100.0;
    float S = (float) sentences / (float) words * 100.0;
    // printf("sentences per 100 words: %f\n", S);
    // printf("letters per 100 words: %f\n", L);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}
