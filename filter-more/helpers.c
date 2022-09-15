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
    return;
}

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagec[height][width];
    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
                imagec[i][j] = image[i][j];
        }
    }

    //grid of x axis
            int gx[3][3];
            gx[0][0] = gx[2][0] = -1;
            gx[1][0] = -2;
            gx[0][1] = gx[1][1] = gx[2][1] = 0;
            gx[0][2] = gx[2][2] = 1;
            gx[1][2] = 2;
    //grid of y axis
            int gy[3][3];
            gy[0][0] = gx[0][2] = -1;
            gy[1][0] = -2;
            gy[1][0] = gx[1][1] = gx[1][2] = 0;
            gy[2][0] = gx[2][2] = 1;
            gy[2][1] = 2;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
                int Gxr, Gxg, Gxb, Gyr, Gyg, Gyb;
                Gxr = Gxg = Gxb = Gyr = Gyg = Gyb = 0;
                for(int y = -1; y < 2; y++)
                {
                    for(int x = 0; x < 3; x++)
                    {

                        if(x + j - 1 < 0 || y + i - 1 < 0 || x + j - 1 > (width - 1) || y + i - 1 > (height - 1))
                        {
                            continue;
                        }else
                        {
                            int rel_x = x + j - 1;
                            int rel_y =  y + i - 1;
                            Gxr = Gxr + image[rel_y][rel_x].rgbtRed * gx[x][y];
                            Gxb = Gxb + image[rel_y][rel_x].rgbtBlue * gx[x][y];
                            Gxg = Gxg + image[rel_y][rel_x].rgbtGreen * gx[x][y];

                            Gyr = Gyr + image[rel_y][rel_x].rgbtRed * gy[x][y];
                            Gyb = Gyb + image[rel_y][rel_x].rgbtBlue * gy[x][y];
                            Gyg = Gyg + image[rel_y][rel_x].rgbtGreen * gy[x][y];
                        }
                    }
                }
                int R, G, B;
                R = round(sqrt((Gxr * Gxr) + (Gyr * Gyr )));
                B = round(sqrt((Gxb * Gxb) + (Gyb * Gyb )));
                G = round(sqrt((Gxg * Gxg) + (Gyg * Gyg )));
                if(R < 255)
                {
                    imagec[i][j].rgbtRed = R;
                }else{
                    imagec[i][j].rgbtRed = 255;
                }
                if(G < 255)
                {
                    imagec[i][j].rgbtGreen = G;
                }else{
                    imagec[i][j].rgbtGreen = 255;
                }
                if(B < 255)
                {
                    imagec[i][j].rgbtBlue = B;
                }else{
                    imagec[i][j].rgbtBlue = 255;
                }

        }
    }
    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
                image[i][j].rgbtRed = imagec[i][j].rgbtRed;
                image[i][j].rgbtBlue = imagec[i][j].rgbtBlue;
                image[i][j].rgbtGreen = imagec[i][j].rgbtGreen;
        }
    }
    return;
}
