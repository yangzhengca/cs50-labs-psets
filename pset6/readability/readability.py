from cs50 import get_string


def main():
    # Prompt to get user input
    text = get_string("Text: ")
    
    # Count letters
    number_letters = count_letters(text)
    
    # Count words
    number_words = count_words(text)
    
    # Count sentences
    number_sentences = count_sentences(text)
    
    # Cal grade
    grade = get_grade(number_letters, number_words, number_sentences)
    
    # Print result
    print_result(grade)
    
# Count letters of string function


def count_letters(text):
    counter = 0
    
    for char in text:
        if char.isalpha():
            counter += 1
    
    return counter


# Count words of string function
def count_words(text):
    counter = 0
    
    for char in text:
        if char == " ":
            counter += 1
    
    return counter + 1


# Count sentences of string function
def count_sentences(text):
    counter = 0
    
    for char in text:
        if char == '.' or char == '!' or char == '?':
            counter += 1
    
    return counter


# Cal grade function
def get_grade(letters, words, sentences):
    
    grade = 0.0588 * letters * 100 / words - 0.296 * sentences * 100 / words - 15.8

    return round(grade)
    
    
# Print grade function
def print_result(grade):
    if grade > 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade ", grade)


if __name__ == "__main__":
    main()    
    