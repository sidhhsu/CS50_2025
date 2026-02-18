#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    uint8_t buffer[512];
    int n = 0;
    char placehold[8];
    FILE *img;
    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            printf("It's a jpg! #%i\n", n);
            if (n != 0)
            {
                fclose(img);
            }
            sprintf(placehold, "%03i.jpg", n);
            img = fopen(placehold, "w");
            if (img == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            fwrite(buffer, 1, 512, img);
            n++;
        }
        else if (n != 0)
        {
            fwrite(buffer, 1, 512, img);
        }

        //printf("%i\n", buffer[0]);
    }
    fclose(img);
    fclose(card);
} // REMEMBER TO FCLOSE EVERYTHING
