while True:
    height = input("Height: ")
    try:
        if 0 < int(height) < 9:
            break
    except:
        pass


def triangle(height, total):
    if height > 1:
        triangle(height-1, total)
    for n in range(total-height):
        print(" ", end="")
    for n in range(height):
        print("#", end="")
    print("  ", end="")
    for n in range(height):
        print("#", end="")
    print()


triangle(int(height), int(height))