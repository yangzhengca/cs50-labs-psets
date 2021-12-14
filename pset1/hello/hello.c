//import required libraries
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get user's name
    string name = get_string("What is your name?\n");
    
    //greeting
    printf("hello, %s\n", name);
}