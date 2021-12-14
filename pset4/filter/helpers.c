#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    int sum;
    // Loop through all pixels, and change all color channels equal to average number of all original color channel numbers
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average = round(sum / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixels, apply sepia algorithm to every color channel of each pixels
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            // Check is sepia color number greater than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed =  sepiaRed;
            image[i][j].rgbtGreen =  sepiaGreen;
            image[i][j].rgbtBlue =  sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half;
    RGBTRIPLE temp;
    // Check the width number is even or odd
    if (width % 2 == 0)
    {
        half = width / 2;
    }
    else
    {
        half = (width - 1) / 2;
    }
    // Exchange value of each pixel(except the middle column when width is odd)
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < half; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Def variables
    float aveRed, aveGreen, aveBlue;
    RGBTRIPLE temp[height][width];
    
    // Loop throught all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Up corner situation, 4 pixels ave
            if (i == 0)
            {
                // Up-left corner
                if (j == 0)
                {
                    aveRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
                    aveGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                                     4.0);
                    aveBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0);
                }
                // Up-right corner
                if (j == width - 1)
                {
                    aveRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 4.0);
                    aveGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                                     4.0);
                    aveBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 4.0);
                }
                // Up edge situation
                if (j != 0 && j != width - 1)
                {
                    aveRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i +
                                    1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                    aveGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 
                                      image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                    aveBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i
                                     + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                }
                
            }
            // Down corner situation, 4 pixels ave
            if (i == height - 1)
            {
                // Down-left corner
                if (j == 0)
                {
                    aveRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                    aveGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) /
                                     4.0);
                    aveBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 4.0);
                }
                // Down-right corner
                if (j == width - 1)
                {
                    aveRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed) / 4.0);
                    aveGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) /
                                     4.0);
                    aveBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) / 4.0);
                }
                // Down edge situation, 6 pixels ave
                if (j != 0 && j != width - 1)
                {
                    aveRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i -
                                    1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                    aveGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                      image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                    aveBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i
                                     - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                }
               
            }
            // Left edge situation, 6 pixels ave
            if (j == 0)
            {
                // except corner
                if (i != 0 && i != height - 1)
                {
                    aveRed = round((image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i -
                                    1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                    aveGreen = round((image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                      image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                    aveBlue = round((image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i
                                     - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0); 
                }
                
            }
            // Right edge situation, 6 pixels ave
            if (j == width - 1)
            {
                // Except corner
                if (i != 0 && i != height - 1)
                {
                    aveRed = round((image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i -
                                    1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0);
                    aveGreen = round((image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                      image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0);
                    aveBlue = round((image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i
                                     - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0); 
                }
            }
            // Middle situation, 9 pixels ave
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                aveRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j +
                                        1].rgbtRed) / 9.0);
                aveGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j -
                                  1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + 
                                  image[i + 1][j + 1].rgbtGreen) / 9.0);
                aveBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                 image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j +
                                         1].rgbtBlue) / 9.0);
            }
            
            // Store blured value in temp array
            temp[i][j].rgbtRed = aveRed;
            temp[i][j].rgbtGreen = aveGreen;
            temp[i][j].rgbtBlue = aveBlue;

            
        }
    }
    // Apply blured data to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    

    return;
}
