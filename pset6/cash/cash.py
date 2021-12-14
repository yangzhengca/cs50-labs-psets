import cs50


def main():
    
    # prompt for user input 
    num = cs50.get_float("Change owed: ")
    while (num <= 0):   
        num = cs50.get_float("Change owed: ")
    
    # Times 100 to users input
    num = num * 100

    # Call get_change function
    result = get_change(num)
    
    # print result
    print(result)
    
    
# Define a function to return numbers of coins
def get_change(number):
    
    counter = 0
    
    while (number >= 25):
        number = number - 25
        counter = counter + 1
    
    while (number >= 10):
        number = number - 10
        counter = counter + 1
    
    while (number >= 5):
        number = number - 5
        counter = counter + 1
        
    while (number >= 1):
        number = number - 1
        counter = counter + 1

    return counter


if __name__ == "__main__":
    main()