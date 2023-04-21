#include <stdio.h>
#include <stdlib.h>
//added by me
#include<stdint.h>
#define Block_Size 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("cannot open file\n");
        return 1;
    }
    typedef uint8_t BYTE;
    //we have a array newfile of char to store name of ith file ie. ###.jpg
    //we will have a counter for the ith jpeg and a pointer to write in that current ith file
    //we will keep checking block wise untill nothing left to read
    int counter = 0;
    char newfile[100];
    FILE *current_file = NULL;
    //open  raw_file
    //repeat untill end
    //block size is 512bytes
    BYTE buffer[Block_Size];
    while (fread(buffer, sizeof(BYTE), Block_Size, raw_file) == Block_Size)
    {
        //check new jpeg file or not
        //bitwise arithmetic
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check first jpeg or not
            if (counter == 0)
            {
                //create a jpegfile
                sprintf(newfile, "%03i.jpg", counter);
                current_file = fopen(newfile, "w");
                fwrite(buffer, sizeof(BYTE), Block_Size, current_file);
                counter++;
            }
            //starting of another jpeg
            else
            {
                fclose(current_file);
                sprintf(newfile, "%03i.jpg", counter);
                current_file = fopen(newfile, "w");
                fwrite(buffer, sizeof(BYTE), Block_Size, current_file);
                counter++;
            }
        }
        //ongoing jpeg
        else if (current_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), Block_Size, current_file);
        }
    }
    //when while loop ends close all
    fclose(current_file);
    fclose(raw_file);
}