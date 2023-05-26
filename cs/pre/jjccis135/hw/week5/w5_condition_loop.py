#!/usr/bin/env python3

userIn = input("Do you have data to enter? Type yes to continue: ")

while userIn.lower() == "yes":
    print("Loop executed")

    userIn = input("Do you have data to enter? Type yes to continue: ")

print("Loop ended")
   