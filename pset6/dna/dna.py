import csv
import sys


def main():
    # Check if uesr input rignt numbers of command line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    
    # Definde and init variables
    origin = []
    result = {}
       
    # Open sequences file, store data in seq variable  
    with open(sys.argv[2], 'r') as file:
        seq = file.read()
    
    # Open csv file, make a copy of the csv data and save in origin;
    # Call max_repeats function with each dna str, save results in result.
    with open(sys.argv[1], 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            origin.append(row)
        for row in reader.fieldnames[1:]:
            max_repeat = max_repeats(seq, row)
            result.update([(row, max_repeat)])
    # Call compare function to compare and print result
    compare(origin, result)
    
# Count max repeats of dna_str in dna_seq function


def max_repeats(dna_seq, dna_str):
    # Define and init variables
    seq_length = len(dna_seq)
    str_length = len(dna_str)
    repeat_counter = 0
    max_repeat_counter = 0
    
    for i in range(0, seq_length-1):
        while (dna_seq[i:i+str_length] == dna_str):
            repeat_counter += 1
            i += str_length

        if repeat_counter > max_repeat_counter:
            max_repeat_counter = repeat_counter

        repeat_counter = 0

    return max_repeat_counter

# Compare result with csv data(in variable origin), and print result


def compare(origin, result):
    is_match = False
    for item in origin:
        is_equal = True
        for key in result:
            if int(item[key]) != result[key]:
                is_equal = False
        if is_equal:
            print(item["name"])
            is_match = True

    if not is_match:
        print("No match")


if __name__ == "__main__":
    main()