#!/usr/bin/env python3

user_filename = input("Enter file name: ")

try:
    file = open(user_filename, "r")

except FileNotFoundError as filenotfoundObject:
    print(filenotfoundObject)
