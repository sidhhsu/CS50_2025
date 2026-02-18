#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            BYTE grayscale = (int) round((image[y][x].rgbtRed + image[y][x].rgbtGreen + image[y][x].rgbtBlue) / 3.0);
            image[y][x].rgbtRed = grayscale;
            image[y][x].rgbtGreen = grayscale;
            image[y][x].rgbtBlue = grayscale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < floor(width / 2.0); x++)
    {
        for (int y = 0; y < height; y++)
        {
            RGBTRIPLE temp = image[y][x];
            image[y][x] = image[y][(width - 1) - x];
            image[y][(width - 1) - x] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int edges = 0;
            int totalred = 0;
            int totalgreen = 0;
            int totalblue = 0;
            for (int xx = -1; xx <= 1; xx++)
            {
                for (int yy = -1; yy <= 1; yy++)
                {
                    if ((x+xx) < 0 || (x+xx) > width - 1 || (y+yy) < 0 || (y+yy) > height - 1)
                    {
                        edges++;
                        continue;
                    }
                    totalred += image[y+yy][x+xx].rgbtRed;
                    totalgreen += image[y+yy][x+xx].rgbtGreen;
                    totalblue += image[y+yy][x+xx].rgbtBlue;
                }
            }
            blurred[y][x].rgbtRed = (int) round(totalred / (9.0 - edges));
            blurred[y][x].rgbtGreen = (int) round(totalgreen / (9.0 - edges));
            blurred[y][x].rgbtBlue = (int) round(totalblue / (9.0 - edges));
        }
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image[y][x] = blurred[y][x];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimg[height][width];
    const int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int gxred = 0;
            int gxgreen = 0;
            int gxblue = 0;
            int gyred = 0;
            int gygreen = 0;
            int gyblue = 0;
            for (int xx = -1; xx <= 1; xx++)
            {
                for (int yy = -1; yy <= 1; yy++)
                {
                    if ((x+xx) < 0 || (x+xx) > width - 1 || (y+yy) < 0 || (y+yy) > height - 1)
                    {
                        continue;
                    }
                    gxred += GX[yy + 1][xx + 1] * image[y+yy][x+xx].rgbtRed;
                    gxgreen += GX[yy + 1][xx + 1] * image[y+yy][x+xx].rgbtGreen;
                    gxblue += GX[yy + 1][xx + 1] * image[y+yy][x+xx].rgbtBlue;

                    gyred += GY[yy + 1][xx + 1] * image[y+yy][x+xx].rgbtRed;
                    gygreen += GY[yy + 1][xx + 1] * image[y+yy][x+xx].rgbtGreen;
                    gyblue += GY[yy + 1][xx + 1] * image[y+yy][x+xx].rgbtBlue;
                }
            }
            double redtest = sqrt(gxred * gxred + gyred * gyred);
            double greentest = sqrt(gxgreen * gxgreen + gygreen * gygreen);
            double bluetest = sqrt(gxblue * gxblue + gyblue * gyblue);
            if (redtest > 255)
            {
                redtest = 255;
            }
            if (greentest > 255)
            {
                greentest = 255;
            }
            if (bluetest > 255)
            {
                bluetest = 255;
            }
            tempimg[y][x].rgbtRed = (int) round(redtest);
            tempimg[y][x].rgbtGreen = (int) round(greentest);
            tempimg[y][x].rgbtBlue = (int) round(bluetest);
        }
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image[y][x] = tempimg[y][x];
        }
    }
    return;
}
