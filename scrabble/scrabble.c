#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Prototypes
int scoreword(string word);
int alphapos(char p);

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ-";
const int numAssignments[27] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0};

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");
    if (scoreword(p1) > scoreword(p2))
    {
        printf("Player 1 Wins!\n");
    }
    else if (scoreword(p2) > scoreword(p1))
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int scoreword(string word)
{
    int score = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        int letter = toupper(word[i]);
        score += numAssignments[alphapos(letter)];
        //printf("Score returns %i\n", score);
    }
    return score;
}

int alphapos(char p)
{
    int x = strlen(alphabet) - 1;
    for (int n = 0; n < x; n++)
    {
        if (p == alphabet[n])
        {
            //printf("N returns %i\n", n);
            return n;
        }
    }
    //printf("X returns %i\n", x);
    return x;
}
