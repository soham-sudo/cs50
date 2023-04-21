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
            //need to substract 1 as arrays are 0 indexed(1 - 100 becomes 0 - 99 i.e 0 - n-1)
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //we will apply edge detection algorith so we need a temp/copy of img
    //we will Gx and Gy
    //we will have a pixel to work with
    //we will create a box around pixel
    //we will apply Sorbel algorithm
    //we will FINALLY transfer values of pixel->img
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    //we need to have Gx and Gy 3x3 matrix (see initialization of 2D array)
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //work on a single pixel starts
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = temp[i][j];
            //store rgb values in a box(array) of 3x3 around a pixel
            RGBTRIPLE box[3][3];
            //populate the box(be careful)
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        //k - (i - 1) is used because box starts from box[0][0] as it is array
                        box[k-i+1][l-j+1] = temp[k][l];

                    }
                    else
                    {
                        box[k - i + 1][l - j + 1].rgbtRed = 0;
                        box[k - i + 1][l - j + 1].rgbtGreen = 0;
                        box[k - i + 1][l - j + 1].rgbtBlue = 0;
                    }
                }
            }
            //till now we have a pixel and a box around a pixel
            //now comes Sorbel Algorithm(finalRed, sumRedx, sumRedy)
            float finalRed = 0;
            int sumRedx = 0;
            int sumRedy = 0;
            float finalGreen = 0;
            int sumGreenx = 0;
            int sumGreeny = 0;
            float finalBlue = 0;
            int sumBluex = 0;
            int sumBluey = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    sumRedx += box[k][l].rgbtRed*Gx[k][l];
                    sumRedy += box[k][l].rgbtRed*Gy[k][l];
                    //for Green
                    sumGreenx += box[k][l].rgbtGreen*Gx[k][l];
                    sumGreeny += box[k][l].rgbtGreen*Gy[k][l];
                    //for Blue
                    sumBluex += box[k][l].rgbtBlue*Gx[k][l];
                    sumBluey += box[k][l].rgbtBlue*Gy[k][l];
                }
            }
            //pow is used to raise x tothe power y
            //there is also sqrt function
            //and a round function to convert to nearest integer
            finalRed = pow(pow(sumRedx, 2) + pow(sumRedy, 2), 0.5);
            pixel.rgbtRed = fmin(round(finalRed), 255);
            //for Green
            finalGreen = pow(pow(sumGreenx, 2) + pow(sumGreeny, 2), 0.5);
            pixel.rgbtGreen = fmin(round(finalGreen), 255);
            //for Blue
            finalBlue = pow(pow(sumBluex, 2) + pow(sumBluey, 2), 0.5);
            pixel.rgbtBlue = fmin(round(finalBlue), 255);
            //finally pixel to image
            image[i][j] = pixel;
        }
    }
    return;
}
