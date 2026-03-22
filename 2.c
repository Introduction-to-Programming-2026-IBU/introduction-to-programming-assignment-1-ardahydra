#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sum = image[row][col].rgbtRed +
                      image[row][col].rgbtGreen +
                      image[row][col].rgbtBlue;

            int avg = round(sum / 3.0);

            image[row][col].rgbtRed = avg;
            image[row][col].rgbtGreen = avg;
            image[row][col].rgbtBlue = avg;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int oldRed = image[row][col].rgbtRed;
            int oldGreen = image[row][col].rgbtGreen;
            int oldBlue = image[row][col].rgbtBlue;

            int newRed = round(0.393 * oldRed + 0.769 * oldGreen + 0.189 * oldBlue);
            int newGreen = round(0.349 * oldRed + 0.686 * oldGreen + 0.168 * oldBlue);
            int newBlue = round(0.272 * oldRed + 0.534 * oldGreen + 0.131 * oldBlue);

            if (newRed > 255)
            {
                newRed = 255;
            }
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image[row][col].rgbtRed = newRed;
            image[row][col].rgbtGreen = newGreen;
            image[row][col].rgbtBlue = newBlue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            temp[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            int counter = 0;

            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        totalRed += temp[i][j].rgbtRed;
                        totalGreen += temp[i][j].rgbtGreen;
                        totalBlue += temp[i][j].rgbtBlue;
                        counter++;
                    }
                }
            }

            image[row][col].rgbtRed = round((float) totalRed / counter);
            image[row][col].rgbtGreen = round((float) totalGreen / counter);
            image[row][col].rgbtBlue = round((float) totalBlue / counter);
        }
    }
}