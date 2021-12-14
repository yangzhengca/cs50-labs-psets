#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt for Number
    long int number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);
    
    // Define card number length
    int length = 0;
    
    // Define card type: 1-AMEX, 2-MASTER, 3-VISA
    int card_type = 0;
    
    // Check if 16th digit is 0 or null
    if (number / 1000000000000000 == 0)
    {
        // Check if 15th digit is 0 or null
        if (number / 100000000000000 == 0)
        {
            // Check the 13th number
            if (number / 1000000000000 == 0)
            {
                printf("INVALID\n");
            }
            else
            {
                // Check the 13th number equal to 4
                if (number / 1000000000000 == 4)
                {
                    card_type = 3;
                    length = 13;
                }
                else
                {
                    printf("INVALID\n");
                }
            }
 
        } 
        else
        {
            // Check the 15th number equal to 3 
            if (number / 100000000000000 == 3) 
            {
                // Check the 14th number equal 4 or 7
                if (number / 10000000000000 == 34 || number / 10000000000000 == 37)
                {
                    card_type = 1;
                    length = 15;
                } 
                else 
                {
                    printf("INVALID\n");
                }
            } 
            else 
            {
                printf("INVALID\n");
            }
            
        } 
    } 
    else 
    {
        // Check the 16th number equal 4
        if (number / 1000000000000000 == 4)
        {
            card_type = 3;
            length = 16;
    
        } 
        // Check the 16th number equal 5
        else if (number / 1000000000000000 == 5)
        {
            if (number / 100000000000000 > 50 && number / 100000000000000 < 56)
            {
                card_type = 2;
                length = 16;         
            } 
            else 
            {
                printf("INVALID\n");
            }    
        } 
        else 
        {
            printf("INVALID\n");
        }
    }
    

    // Check if valid card number match the Luhn’s Algorithm
    if (card_type != 0)
    {
        // Define and initailize variables
        int result = 0;
        int pos = 0;

        // Calculate sum of every other numbers and other numbers
        while (number != 0)
        {
            if (pos % 2 != 0)
            {
                int temp = 2 * (number % 10);
                if (temp > 9)
                {
                    result += (temp % 10 + 1);  
                } 
                else 
                {
                    result += temp;
                }
            } 
            else 
            {
                result += number % 10;
            }
            number = number / 10;
            pos ++;
        }
        
        // If card number match the Luhn’s Algorithm, print card type
        if (result % 10 == 0)
        {
            if (card_type == 1)
            {
                printf("AMEX\n");    
            } 
            else if (card_type == 2)
            {
                printf("MASTERCARD\n");
            } 
            else if (card_type == 3)
            {
                printf("VISA\n");
            } 
            else
            {
                    
            }
        } 
        else
        {
            // If card number doesn't match the Luhn’s Algorithm, print invalid
            printf("INVALID\n");
        }
        
    } 
    else 
    {

    }
    
    

}