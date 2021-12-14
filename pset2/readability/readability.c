#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int conut_letters(string text);

int count_words(string text);

int count_sentences(string text);

int get_grade(int letters, int words, int sentences);

int print_result(int grade);

int main(void)
{
    // Get user input 
    string text = get_string("Text: ");
    
    
    // Count letters
    int number_letters = conut_letters(text);
    
    // printf("%i letter(s)\n", number_letters);
    
    
    // Count words, seprated by space
    int number_words = count_words(text);
    
    // printf("%i word(s)\n", number_words);
    
    
    // Count sentences
    int number_sentences = count_sentences(text);
    
    // printf("%i sentence(s)\n", number_sentences);
    
    
    // Get grade index
    int grade = get_grade(number_letters, number_words, number_sentences);
    
    // printf("Grade %i\n", grade);
    
    
    // Print the result
    print_result(grade);
}


// Count letters from given string function
int conut_letters(string text)
{
    int counter = 0;
    // Loop all char in string
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // If char is a letter, count_letters + 1
        // isalpha is a function from ctype.h - check whether a character is alphabetical
        if (isalpha(text[i]))
        {
            counter++;
        }
    }
    return counter;
}


// Count words from given string function
int count_words(string text)
{
    int counter = 0;
    // Loop all char in string
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // If char is a space, count_space + 1
        if (text[i] == ' ')
        {
            counter ++;
        }
    }
    return counter + 1;
}


// Count sentences from given string function
int count_sentences(string text)
{
    int counter = 0;
    // Loop all char in string
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // If char is '.', '!' or '?', count + 1
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}



// Get grade index using the Coleman-Liau formula
int get_grade(int letters, int words, int sentences)
{

    float index;

    index = 0.0588 * letters * 100 / words - 0.296 * sentences * 100 / words - 15.8;

    return round(index);
}

// Print result function
int print_result(int grade)
{
    if (grade > 16)
    {
        printf("Grade 16+\n");
    } 
    else if (grade < 1) 
    {
        printf("Before Grade 1\n");
    }
    else 
    {
        printf("Grade %i\n", grade);
    }
}


