#!/usr/bin/env python3

# Welcome message
print("Welcome, this program will ask you for 3 numbers and display the highest, middle, and lowest number\n")

# User In
num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: ")) 
num3 = int(input("Enter third number: "))

if (num1 < num2 and num1 < num3):
    print("\nNumber {0:d} is the lowest value".format(num1))

elif (num1 > num2 and num1 < num3):
    print("\nNumber {0:d} is the middle value".format(num1))

elif (num1 > num2 and num1 > num3):
    print("\nNumber {0:d} is the greatest value".format(num1))

if (num2 < num1 and num2 < num3):
    print("\nNumber {0:d} is the lowest value".format(num2))

elif (num2 > num1 and num2 < num3):
    print("\nNumber {0:d} is the middle value".format(num2))

elif (num2 > num1 and num2 > num3):
    print("\nNumber {0:d} is the highest value".format(num2))
    
if (num3 < num1 and num3 < num2):
    print("\nNumber {0:d} is the lowest value".format(num3))

elif (num3 > num1 and num3 < num2):
    print("\nNumber {0:d} is the middle value".format(num3)) 

elif (num3 > num1 and num3 > num2):
    print("\nNumber {0:d} is the highest value".format(num3))




















