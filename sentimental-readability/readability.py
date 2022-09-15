from cs50 import get_string

# intialize required variables
letters = 0
sentences = 0
words = 0

# obtain the paragraph
para = get_string("Text: ")

# iterate over each character and update the score and sentences
for letter in para:
    if letter.isalpha():
        letters += 1
    elif ord(letter) == ord(" "):
        words += 1
    elif ord(letter) == ord(".") or ord(letter) == ord("?") or ord(letter) == ord("!"):
        sentences += 1

words += 1
# calculate the value of L
L = (letters / words) * 100
#calculate S
S = (sentences / words) * 100
# caculate index
index = 0.0588 * L - 0.296 * S - 15.8

# Print out the grade
if(index >= 16):
    print("Grade 16+")
elif (index < 1):
    print("Before Grade 1")
else:
    grade = round(index, 0)
    print(f"Grade {int(grade)}")
