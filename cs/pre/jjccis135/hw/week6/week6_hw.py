#!/usr/bin/env python3

# Welcome
print("Welcome... Type in numbers and this program will output the average")

# Globals
count = 0 # init global count 
sum = 0 # init glabal sum
# userin start
userin = int(input("Enter Number (-99 to quit): "))

# Loop start 
while userin != -99:
    count += 1 # update count
    sum += userin # update sum

    # repeat userin
    userin = int(input("Enter Number (-99 to quit): "))

# Check if -99 was first value
if sum != 0:
    avg = float(sum / count) # compute average
    print(f"Average: {avg}") # output

# Exit with average 0 if -99 was first input
else:
    print("Average: 0")