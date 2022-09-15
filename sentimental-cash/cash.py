from cs50 import get_float

owed = 0.00
quarters = 0
dimes = 0
nickels = 0
pennies = 0

#function to calculatequarters
def calqua():
    return int((owed - (owed % 0.25)) / 0.25)

#function to calculate dimes
def caldimes():
    return int((owed - (quarters * 0.25 + (owed % 0.10))) / 0.10)

#function to calculate nickels
def calnick():
    return int(round((owed - (quarters * 0.25 + dimes * 0.10 )), 2) / 0.05)

#function to calculate dimes
def calpen():
    return int(round((owed - (quarters * 0.25 + dimes * 0.10 + nickels * 0.05 )), 2) / 0.01)
#obtain the amount owed
while owed <= 0:
    owed = get_float("Change owed: ")

#caculate the number of coins
quarters = calqua()
dimes = caldimes()
nickels = calnick()
pennies = calpen()


#calculate total coins
total = quarters + nickels + dimes + pennies

#print out the number of coins
print(total)


