
height = input("Height: ")

# Prompt for height, height must be an integer and between or equal to 1 and 8
while (not height.isdigit() or int(height) > 8 or int(height) < 1):   
    height = input("Height: ")

# convert str to int
height = int(height)


# print pattern
for i in range(1, height+1):
    for j in range(height - i):
        print(" ", end="")
    
    for k in range(i):
        print("#", end="")
    
    print("  ", end="")
    
    for k in range(i):
        print("#", end="")
        
    print("")
