#!/usr/bin/env python3

# Includes
import os
import sys

def DoubleSelection():
    """ Hw Program Double Selection """

    # Collect User Input
    userIn = input("Enter (y) for yes: ")

    # Print Yes for input "yes", else print no
    if userIn == "y": 
        print("You Have selected Yes")
    else:
        print("Invalid Input")

def main():
    """ Entry """
    
    # Clear
    if sys.platform == "linux": os.system("clear")
    if sys.platform == "windows": os.system("cls")

    DoubleSelection()
    return 0

if __name__ == '__main__':
    main()







































