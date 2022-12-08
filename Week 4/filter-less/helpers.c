#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t r, g, b, average;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            average = round(((float) image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float r, g, b;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            r = image[h][w].rgbtRed * 0.393 + image[h][w].rgbtGreen * 0.769 + image[h][w].rgbtBlue * 0.189;
            g = image[h][w].rgbtRed * 0.349 + image[h][w].rgbtGreen * 0.686 + image[h][w].rgbtBlue * 0.168;
            b = image[h][w].rgbtRed * 0.272 + image[h][w].rgbtGreen * 0.534 + image[h][w].rgbtBlue * 0.131;
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            image[h][w].rgbtRed = round(r);
            image[h][w].rgbtGreen = round(g);
            image[h][w].rgbtBlue = round(b);
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
    }
    else
    {
        ct = 1;
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width - ct) / 2; w++)
        {
            //printf("%i, %i\n", h, w);
            RGBTRIPLE buffer[height][width];
            buffer[h][w] = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = buffer[h][w];
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
    int minh, maxh, minw, maxw;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //printf("%i, %i\n", w, h);
            if (w >= 1 && h >= 1 && h < height - 1 && w < width - 1)
            {
                minh = -1;
                maxh = 1;
                minw = -1;
                maxw = 1;
            }
            else if (w == (width - 1) && h == (height - 1))
            {
                minh = -1;
                maxh = 0;
                minw = -1;
                maxw = 0;
            }
            else if (w == 0 && h == (height - 1))
            {
                minh = -1;
                maxh = 0;
                minw = 0;
                maxw = 1;
            }
            else if ((w == width - 1) && h == 0)
            {
                minh = 0;
                maxh = 1;
                minw = -1;
                maxw = 0;
            }
            else if (w == 0 && h >= 1 && (h < height - 1))
            {
                minh = -1;
                maxh = 1;
                minw = 0;
                maxw = 1;
            }
            else if ((w == width - 1) && h >= 1 && (h < height - 1))
            {
                minh = -1;
                maxh = 1;
                minw = -1;
                maxw = 0;
            }
            else if (w >= 1 && h == 0 && (w < width - 1))
            {
                minh = 0;
                maxh = 1;
                minw = -1;
                maxw = 1;
            }
            else if (w >= 1 && h == (height - 1) && w < width - 1)
            {
                minh = -1;
                maxh = 0;
                minw = -1;
                maxw = 1;
            }
            else if (w == 0 && h == 0)
            {
                minh = 0;
                maxh = 1;
                minw = 0;
                maxw = 1;
            }
            else
            {
                minh = 0;
                maxh = 0;
                minw = 0;
                maxw = 0;
            }
            double r = 0, g = 0, b = 0, counter = 0;
            for (int i = minh; i <= maxh; i++)
            {
                for (int j = minw; j <= maxw; j++)
                {
                    r += new_image[h + i][w + j].rgbtRed;
                    b += new_image[h + i][w + j].rgbtBlue;
                    g += new_image[h + i][w + j].rgbtGreen;
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
