#include "helpers.h"

#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //may or maynot use a variable
            RGBTRIPLE pixel = image[i][j];
            //using a single float int arithmetic operation will produce result in float and we have accurate roundoff
            int avg = round((pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen)/3.0);
            pixel.rgbtBlue = pixel.rgbtRed = pixel.rgbtGreen = avg;
            image[i][j] = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
   for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //may or maynot use a variable
            RGBTRIPLE pixel = image[i][j];

            //sepia formulas
            int sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            int sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            int sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);
            //fmin function already present in math.h
            pixel.rgbtRed = fmin(sepiaRed, 255);
            //another way of writing/comparing and returning
            pixel.rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            pixel.rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[i][j] = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //only swap the half part remainning is already swapped
        for (int j = 0; j < width / 2; j++)
        {
            //vertical flip in a row 2 columns gets interchanged
            RGBTRIPLE temp = image[i][j];
            //need to substract 1 as arrays are 0 indexed
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //we will keep changing pixels in img and use original values from copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //work on pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = copy[i][j];
            //WE NEED TO USE INT OR FLOAT DATATYPES variables FOR STORING VALUES AND DOING CALCULATION,..
            //DO NOT USE BYTE(I.E pixel.red etc otherwise it have calculation mistake)
            int red = 0;
            int green = 0;
            int blue = 0;
            //bluring and counting how many boxes around a pixel are valid
            float count = 0;
            for (int l = i - 1; l < i + 2; l++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    if ((l >= 0 && l < height) && (m >= 0 && m < width))
                    {
                        red += copy[l][m].rgbtRed;
                        green += copy[l][m].rgbtGreen;
                        blue += copy[l][m].rgbtBlue;
                        count ++;
                    }
                }
            }
            //avg
            pixel.rgbtRed = round(red / count);
            pixel.rgbtGreen = round(green / count);
            pixel.rgbtBlue = round(blue / count);
            //actually bluring a pixel
            image[i][j] = pixel;
        }
    }
    return;
}
