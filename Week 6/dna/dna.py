import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python ./dna.py [sth]")
        sys.exit(1)

    # TODO: Read database file into a variable
    f = open(sys.argv[1])
    DICT = csv.DictReader(f)
    KEYS = DICT.fieldnames
    # print(KEYS)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as f:
        DNA = f.read()
        # print(DNA)

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for n in KEYS[1:]:
        result = longest_match(DNA, n)
        matches[n] = result
    # print(matches)
    FOUND = False
    # TODO: Check database for matching profiles
    for row in DICT:
        # print()
        # print()
        itis = True
        for key in KEYS[1:]:
            if int(row[key]) != int(matches[key]):
                # print("False")
                itis = False
        if itis == True:
            print(row["name"])
            FOUND = True
    if not FOUND:
        print("No match")
    f.close()
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
