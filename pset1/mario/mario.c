#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt for height, height must between or equal to 1 and 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    
    // Print required pattern
    int i, j, k;

    // Print row i
    for (i = 1; i <= height; i++)
    {
        // Print spaces before
        for (j = height - i; j > 0; j--)
        {
            printf(" ");
        }
        
        // Print left blocks 
        for (k = 0; k < i; k++)
        {
            printf("#"); 
        }
        
        // Print middle spaces
        printf("  ");
        
        // Print right blocks
        for (k = 0; k < i; k++)
        {
            printf("#"); 
        }
        
        // Change line
        printf("");
    }
}