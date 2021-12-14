#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Check if image can be opened
    FILE *image = fopen(argv[1], "r");
    if (image == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Define variables
    BYTE buffer[512];
    int file_counter = 0;
    char filename[10];
    FILE *jpeg = NULL;
    
    // Loop through image by chunck of 512 bytes(store in buffer)
    while (fread(buffer, sizeof(BYTE), 512, image))
    {
        // Check if buffer is a jpeg file header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // First founded jpeg file
            if (file_counter == 0)
            {
                sprintf(filename, "%03i.jpg", file_counter);
                file_counter++;
                jpeg = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, jpeg);
            }
            // other than first founded jpeg file
            else
            {
                fclose(jpeg);
                sprintf(filename, "%03i.jpg", file_counter);
                file_counter++;
                jpeg = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, jpeg);
            }
        }
        else
        {
            // If already found jpeg file, write data to file
            if (file_counter != 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, jpeg);
            }
        }
    }
    // Close all opened files
    fclose(jpeg);
    fclose(image);
    
}