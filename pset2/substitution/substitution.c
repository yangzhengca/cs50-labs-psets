#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Declaration key validate function
bool key_validate(string keys);


int main(int argc, string argv[])
{
    // Call key validate function
    bool is_validate = key_validate(argv[1]);
    
    // Check key validate function result
    if (is_validate)
    {
        // Get plaintext from user
        string plaintext = get_string("plaintext: ");
        
        // Substitute each letter and print result
        printf("ciphertext: ");

        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            if (isupper(plaintext[i]))
            {
                int m = plaintext[i] - 'A';
                char n = toupper(argv[1][m]);
                printf("%c", n);
            } 
            else if (islower(plaintext[i]))
            {
                int m = plaintext[i] - 'a';
                char n = tolower(argv[1][m]);
                printf("%c", n);
            }
            else
            {
                printf("%c", plaintext[i]);
            }

        }
        
        printf("\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

// Key calidate function
bool key_validate(string keys)
{
    // check if user input a key
    if (keys == NULL)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    
    // check if all characters in keys are alphabetic character
    for (int i = 0, len = strlen(keys); i < len; i++)
    {
        if (!isalpha(keys[i]))
        {
            printf("Usage: ./substitution key\n");
            return false;
        }
    }
    
    // Check if keys length is 26
    if (strlen(keys) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    
    // Check if there is duplicate character
    for (int i = 0, len = strlen(keys); i < len; i++)
    {
        for (int j = i + 1; j < strlen(keys); j++)
        {
            if (keys[i] == keys[j])
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    
    return true;
}