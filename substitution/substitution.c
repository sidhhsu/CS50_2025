#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int checkalphabet(string key);

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution Key\n");
        return 1;
    }
    else if (checkalphabet(argv[1]) == 1) // if argv has 26 letters, each letter of alphabet once, and no numbers
    {
        const string plain = get_string("plaintext: ");
        char cipher[strlen(plain) + 1];
        cipher[strlen(plain)] = '\0';
        char temp;
        for (int i = 0; i < strlen(plain); i++)
        {
            if (!isalpha(plain[i]))
            {
                //printf("%c is not a letter\n", plain[i]);
                cipher[i] = plain[i];
                continue;
            }
            temp = toupper(plain[i]); // work it in uppercase then convert it back later
            for (int pos = 0; pos < strlen(alphabet); pos++)
            {
                if (temp == alphabet[pos])
                {
                    //printf("converting: %c ", plain[i]);
                    temp = toupper(argv[1][pos]);
                    //printf("to %c\n", temp);
                    if (islower(plain[i])) // convert back to lowercase
                    {
                        cipher[i] = tolower(temp);
                    }
                    else
                    {
                        cipher[i] = toupper(temp);
                    }
                    break;
                }
            }
        }
        printf("ciphertext: %s\n", cipher);
        return 0;
    }
    else
    {
        printf("Key must contain each letter of the alphabet exactly once.\n");
        return 1;
    }

}

int checkalphabet(string key)
{
    for (int a = 0; a < strlen(alphabet); a++)
    {
        int counter = 0;
        //printf("Letter: %c\n", alphabet[a]);
        for (int b = 0; b < strlen(key); b++)
        {
            if (alphabet[a] == toupper(key[b]))
            {
                counter++;
                //printf("%i\n", counter);
            }
        }
        if (counter != 1)
        {
            return 0;
        }
    }
    return 1;
}
