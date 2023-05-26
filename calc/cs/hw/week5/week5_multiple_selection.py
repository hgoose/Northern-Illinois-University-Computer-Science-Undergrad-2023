#!/usr/bin/env python3

# Nathan Warner
# Cis 
# 9/22/2022

# Includes
import os

def main():
    """ Multiple Selection """
    os.system("clear")

    # Gather User in 
    userIn = input("Enter (y) for yes (n) for no: ").lower()

    # Selection Statments 
    if userIn == "y":
        print("You have selected yes")
    elif userIn == "n":
        print("you have selected no")
    else:
        print("Invalid Input")

if __name__ == '__main__':
    main()
