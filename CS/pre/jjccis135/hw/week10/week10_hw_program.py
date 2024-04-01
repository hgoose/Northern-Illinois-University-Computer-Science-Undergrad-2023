#!/usr/bin/env python3
# Author: Nate Warner
# Class: Cis 135
# Program: Create an inventory system using two parallel lists and functions.

def search_inventory(part_list, price_list):
    """ Function searchs list for part """

    # Locals
    user_search = str()
    user_search = input("Name of part: ").lower()

    # LCV
    index = int()

    # If user attempts to search for part with no items added yet.
    if len(parts_list) == 0:
        print("\nitem \"{}\" not found".format(user_search))

    while index < len(part_list):
        
        # If item found, print price
        if part_list[index] == user_search:
            print("Price of part: ${}".format(price_list[index]))
            break
        
        # update index
        index += 1

        # if reached last iteration and hasnt found item, print not found
        if index == len(part_list):
            print("\nitem \"{}\" not found".format(user_search))


def add_to_inventory(part_list, price_list):
    """ Function for user to add items to inventory """

    # Locals
    user_part = str()
    user_price = float()

    # User Input
    user_part = input("Enter part: ")
    user_price = float(input("Enter Price: "))

    # Add user input to corresponding list
    part_list.append(user_part)
    price_list.append(user_price)

    # Success message
    print("Item added Successfully") 


def display_inventory(part_list, price_list):
    """ Function to display inventory """

    # Display headers
    print("Part  \t  Price")
    
    # LCV
    index = int()

    # Loop
    while index < len(part_list):
        print("{0:10s}{1:.2f}".format(part_list[index], price_list[index]))
        index += 1


def display_menu():
    """ Function to display menu """

    print("""
Welcome to the JJC Inventory System
1. Add to inventory
2. Check price
3. Display inventory
4. Exit """)

	# Local
    user_menu_choice = int()

	# Input
    user_menu_choice = int(input("Your choice: "))
    print()

    # Return
    if user_menu_choice not in [1,2,3,4]:
        print("Invalid input")
    return user_menu_choice


# Mainline

# Empty lists 
parts_list = []
price_list = []

# LCV
user_menu_choice = int()

# Loop to display menu and call appropriate function based on input
while user_menu_choice != 4:
    user_menu_choice = display_menu()

    if user_menu_choice == 1:
        add_to_inventory(parts_list, price_list)

    elif user_menu_choice == 2:
        search_inventory(parts_list, price_list)

    elif user_menu_choice == 3:
        display_inventory(parts_list, price_list)




