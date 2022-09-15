from cs50 import get_int

height = 0
#pbtain the height of the required pyramid
while height < 1 or height > 8:
    height = get_int("Height: ")

#printout the pyramid
for i in range(0, height):
    print(" " * (height - 1 - i) + "#" * (i + 1) + "  " + "#" * (i + 1))
