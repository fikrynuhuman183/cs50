import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    persons = []
    with open(sys.argv[1], "r") as t:
        reader = csv.reader(t)

        # obtain the different str sequences
        rowh = next(reader)

        # assign them into a list
        seq = []
        for i in range(1, len(rowh)):
            seq.append(rowh[i])

        # create a list of persons which contain the data of each person in a list
        for row in reader:
            person = []
            person.append(row[0])
            for i in range(1, len(row)):
                person.append(int(row[i]))
            persons.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as s:
        sequence = s.read()
    # TODO: Find longest match of each STR in DNA sequence

    # store the data in the given sequence in a list
    seqg = []
    for i in range(1, len(row)):
        seqg.append(longest_match(sequence, seq[i - 1]))

    # TODO: Check database for matching profiles
    # Boolean to store if the persons sequence matchesthe data
    match = False
    # iterate through the list of lists(person)
    for i in range(0, len(persons)):
        #a counter to remember the number of correct matches
        counter = 0
        for j in range(1,len(row)):
            if persons[i][j] == seqg[j-1]:
                counter += 1
        #if the counter has the correct number of matches set the match to true and store the index of person in a variable
        if counter == (len(row) - 1):
            match = True
            person_m = i
    if match == True:
        print(persons[person_m][0])
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
