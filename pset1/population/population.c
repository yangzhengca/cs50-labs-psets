#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size, start size must greater than 9
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    
    //  Prompt for end size, end size must greater or equal to start size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    
    // Calculate number of years until we reach threshold, Print number of years
    int n = 0;
    
    // when start size is equal to end size, use 0 year.
    if (start == end)
    {
        printf("Years: %i\n", n);    
    }
    else
    {
        do
        {
            start = start + start / 3 - start / 4;
            n++;
        }
        while (start < end);
        printf("Years: %i\n", n); 
    }
}