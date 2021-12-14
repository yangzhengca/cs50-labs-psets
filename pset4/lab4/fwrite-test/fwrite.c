// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 3)
    {
        printf("Usage: ./volume input.wav output.wav\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }



    // TODO: Copy header from input file to output file
    char a;
    
    fread(&a, sizeof(char), 1, input);
    fwrite(&a, sizeof(char), 1, output);


    // TODO: Read samples from input file and write updated data to output file
    
    char b;
    
    while (fread(&b, sizeof(char), 1, input))
    {
        b= b*2;
        fwrite(&b, sizeof(char), 1, output);
    };
    

    // Close files
    fclose(input);
    fclose(output);
}
