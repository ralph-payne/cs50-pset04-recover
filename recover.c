// CS50 pset04. Completed on 10 April 2020
// This doesn't work well on local machine as it only returns one jpeg
// However, it does work on the CD50 IDE

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Did you mean:\n./recover.exe card.raw\n");
        return 1;
    }

    // Declare file pointer which points to card.raw
    FILE *file_ptr_card;
    // Open file
    file_ptr_card = fopen(argv[1], "r");

    // Perform null check
    if (!file_ptr_card)
    {
        return 2;
    }

    // Declare buffer variable of size 512
    unsigned char buffer[BLOCK_SIZE];

    // Initialise photo counter to zero
    int photo_number = 0;

    // feof checks if the end of the given file stream has been reached
    while (!feof(file_ptr_card))
    {
        int read_result = fread(buffer, sizeof(char), 512, file_ptr_card);

        if (read_result)
        {
            // Declare empty string that will hold filename
            char jpg_name[8] = "";

            // If start of buffer contains jpeg signature, start writing to new file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
            {
                sprintf(jpg_name, "%03i.jpg", photo_number);
                // Open jpeg file in write mode
                FILE *jpeg_file = fopen(jpg_name, "w");
                fwrite(&buffer, BLOCK_SIZE, 1, jpeg_file);
                fclose(jpeg_file);
                photo_number++;
            }
            // If photo number is equal to zero, and you haven't started writing, do nothing
            else if (!photo_number)
            {
                printf("Skipping block as haven't hit jpeg signature yet\n");
            }
            else
            {
                sprintf(jpg_name, "%03i.jpg", photo_number - 1);
                // "a" for append
                FILE *jpeg_file = fopen(jpg_name, "a");
                fwrite(&buffer, BLOCK_SIZE, 1, jpeg_file);
                fclose(jpeg_file);
            }
        }
        // If read_result is equal to zero, break
        else
        {
            break;
        }
    }

    printf("Total number of photos found: %d\n", photo_number);
    fclose(file_ptr_card);

    // Return zero to indicate success
    return 0;
}
