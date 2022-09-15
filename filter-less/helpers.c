#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float Blue = image[i][j].rgbtBlue;
            float Red = image[i][j].rgbtGreen;
            float Green = image[i][j].rgbtRed;
            int avg = round((Blue + Red + Green) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;
            float  originalRed= image[i][j].rgbtRed;


            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
        for(int j = 0; j < width/2; j++)
            {
                RGBTRIPLE temp = image[i][width-1-j];
                image[i][width-1-j] = image[i][j];
                image[i][j] = temp;
            }
        }
        else
        {
            for(int j = 0; j < (width + 1)/2; j++)
            {
                RGBTRIPLE temp = image[i][width-1-j];
                image[i][width-1-j] = image[i][j];
                image[i][j] = temp;
            }
        }
    }
    return;}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagenew[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int n_valid = 0;
            float red, blue, green;
            red = blue = green = 0;

                for(int y = -1; y < 2; y++)
                {
                    for(int x = -1; x < 2; x++)
                    {
                        int rel_x = j + x;
                        int rel_y = i + y;
                        if(rel_x < 0 || rel_y < 0 || rel_x > (width - 1) || rel_y > (height - 1))
                        {
                            continue;
                        }else{
                        n_valid++;
                        red = red + image[rel_y][rel_x].rgbtRed;
                        blue = blue + image[rel_y][rel_x].rgbtBlue;
                        green = green + image[rel_y][rel_x].rgbtGreen;
                        }
                    }
                }

            imagenew[i][j].rgbtRed = round(red / n_valid);
            imagenew[i][j].rgbtBlue = round(blue / n_valid);
            imagenew[i][j].rgbtGreen = round(green / n_valid);
        }
    }

    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
                image[i][j] = imagenew[i][j];
        }
    }
    return;
}
