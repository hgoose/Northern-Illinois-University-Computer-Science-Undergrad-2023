#!/usr/bin/env python3
""" 
Program: Calculate gas milage and cost of tank
Author: Nate Warner
Assignment: Lab 02
"""
# Imports
import os

# Clears screen if ran in terminal
os.system("cls")

# Print Welcome Message
print("Welcome... This program will calculate gas milage and as the cost of one full tank for your vehicle \n")

# Gather user input
total_miles = int(input("Enter the total ammount of miles your car gets per full tank: "))
price_per_gallon = float(input("Enter the price for one gallon of gas at your gas station: $"))
size_of_tank = float(input("Enter the size of your tank (in gallons): "))

# Preform Calculations
calculate_gas_milage = int(total_miles / size_of_tank  )
calculate_cost = float(size_of_tank * price_per_gallon)

# Output to screen
print("\nmpg: %s" % (calculate_gas_milage, ))
print("\nCost: $%s" % (calculate_cost, )) 

# Exit
input("\nPress any key to exit program: ")
print("\nGoodbye")
