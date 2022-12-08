from cs50 import get_string
import numpy as np
to_ev = get_string("Text: ")


def readability(text):
    words = text.count(' ') + 1  # OK
    S = ((text.count('!') + text.count('.') + text.count('?')) / words) * 100
    L = 0
    for t in text:
        if t.isalpha():
            L += 1

    L = (L / words) * 100
    read = int(np.round(0.0588 * L - 0.296 * S - 15.8))
    # print(f"{words}/{L}/{S}/{read}")
    if read < 1:
        print("Before Grade 1")
    elif read < 16:
        print(f"Grade {read}")
    else:
        print("Grade 16+")


readability(to_ev)