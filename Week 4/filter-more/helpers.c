#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t r, g, b, average;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            average = round(((float) image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue)/3.0);
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int ct ;
    if (width % 2 == 0)
    {
        ct = 0;
    }else
    {
        ct = 1;
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width-ct)/2; w++)
        {
            //printf("%i, %i\n", h, w);
            RGBTRIPLE buffer[height][width];
            buffer[h][w] = image[h][w];
            image[h][w] = image[h][width-w-1];
            image[h][width-w-1] = buffer[h][w];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            new_image[h][w].rgbtRed = image[h][w].rgbtRed;
            new_image[h][w].rgbtBlue = image[h][w].rgbtBlue;
            new_image[h][w].rgbtGreen = image[h][w].rgbtGreen;
        }
    }
    int min_i, max_i, min_j, max_j;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //printf("%i, %i\n", w, h);
            if (w >= 1 && h >= 1 && h < height-1 && w < width-1)
            {
                min_i = -1;
                max_i = 1;
                min_j = -1;
                max_j = 1;
            }
            else if (w == (width-1) && h == (height-1))
            {
                min_i = -1;
                max_i = 0;
                min_j = -1;
                max_j = 0;
            }
            else if (w == 0 && h == (height-1))
            {
                min_i = -1;
                max_i = 0;
                min_j = 0;
                max_j = 1;
            }
            else if (w == (width-1) && h == 0)
            {
                min_i = 0;
                max_i = 1;
                min_j = -1;
                max_j = 0;
            }
            else if (w == 0 && h >= 1 && h < height-1)
            {
                min_i = -1;
                max_i = 1;
                min_j = 0;
                max_j = 1;
            }
            else if (w == (width-1) && h >= 1 && h < height-1)
            {
                min_i = -1;
                max_i = 1;
                min_j = -1;
                max_j = 0;
            }
            else if (w >= 1 && h == 0 && w < width-1)
            {
                min_i = 0;
                max_i = 1;
                min_j = -1;
                max_j = 1;
            }
            else if (w >= 1 && h == (height-1) && w < width-1)
            {
                min_i = -1;
                max_i = 0;
                min_j = -1;
                max_j = 1;
            }
            else if (w == 0 && h == 0)
            {
                min_i = 0;
                max_i = 1;
                min_j = 0;
                max_j = 1;
            }
            else{
                min_i = 0;
                max_i = 0;
                min_j = 0;
                max_j = 0;
            }
            double r = 0, g = 0, b = 0, counter = 0;
            for (int i = min_i; i <= max_i; i++)
            {
                for (int j = min_j; j <= max_j; j++)
                {
                    r += new_image[h+i][w+j].rgbtRed;
                    b += new_image[h+i][w+j].rgbtBlue;
                    g += new_image[h+i][w+j].rgbtGreen;
                    counter++;
                }
            }
            r /= counter;
            g /= counter;
            b /= counter;
            image[h][w].rgbtRed = round(r);
            image[h][w].rgbtGreen = round(g);
            image[h][w].rgbtBlue = round(b);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
