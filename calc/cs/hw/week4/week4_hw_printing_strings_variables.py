#!/usr/bin/env python3

# Author: Nate Warner
# Program: Printing strings and variables
# Cis 135
# Date: 9/15/2022

# Includes
import os
import sys

def HwProgram():
    """ Articles of rubric """

    # declare variables
    hw = str("Hello World")
    countdown = float(0.12345)

    # Prints
    print(hw)
    print(countdown)
    print("\nthe value of hello world is {0:s}\n".format(hw))
    print("the value of countdown is  {0:.5f}".format(countdown))
    print("the value of countdown is  {0:.4f}".format(countdown))
    print("the value of countdown is  {0:.3f}".format(countdown))
    print("the value of countdown is  {0:.2f}".format(countdown))
    print("the value of countdown is  {0:.1f}".format(countdown))
    print("the value of countdown is  {0:.0f}\n".format(countdown))

def main():
    """ main """

    # os checks
    if sys.platform == "linux": os.system("clear")
    if sys.platform == "windows": 
        os.system("cls") # Clear buffer (win)
    
    HwProgram() # Call main function
    return 0  # exit_success

if __name__ == '__main__':
    main()


