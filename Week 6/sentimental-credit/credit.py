from cs50 import get_string

x = get_string("Number: ")


def validate(number):
    n = 0
    number = number[::-1]
    for index, value in enumerate(number):
        if ((index % 2) != 0):
            #print(index, value)
            new = int(value) * 2
            if new > 9:
                n += new % 10
                n += int(new / 10)
            else:
                n += new

        else:
            #print(index, "2", value)
            n += int(value)
    if (n % 10) == 0:
        return True
    else:
        return False


result = validate(x)
if (len(x) == 15 and ((x[0] + x[1]) == "34") or ((x[0] + x[1]) == "37")) and result:
    print("AMEX")

elif (len(x) == 16 and ((x[0] + x[1]) == "51") or ((x[0] + x[1]) == "52") or ((x[0] + x[1]) == "53") or ((x[0] + x[1]) == "54") or ((x[0] + x[1]) == "55")) and result:
    print("MASTERCARD")

elif ((len(x) == 13) or (len(x) == 16)) and (x[0] == "4") and result:
    print("VISA")

else:
    print("INVALID")