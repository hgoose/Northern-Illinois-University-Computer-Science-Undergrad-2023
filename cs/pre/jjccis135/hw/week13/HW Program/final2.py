# Author: Nate Warner
# Class: CIS 135
# Date: 11/19/22
# Program: Write a program that handles IT equipment inventory by writing to and reading from a plain text file.

# USER DEFINED FUNCTIONS #

def writeSeperator(file):
    """ Write Seperator to file """
    file.write(",\n")


def checkQuitandWriteEquipment(file, _equipment):
    """ Function to check quit (as to not duplicate lines) """
    if not _equipment == "quit":
        file.write(_equipment)


def writeNumOnHand(file, _num_onhand):
    """ write num_onhand to file """
    file.write(_num_onhand)

def writeCost(file, _cost):

    """ write cost to file """
    file.write(_cost)


def computeTotal(_list):
    """ Compute Total """

    product = int()
    product_iteration = int()
    product_list = []

    for i in range(1, len(_list), 3):
        product_iteration = int(_list[i]) * float(_list[i+1])
        product_list.append(product_iteration)

    for item in product_list:
        product += item

    return product

# MAIN #
    """ Entry """


def main():

    # Declare needed variables

    equipment = str()
    num_onhand = str()
    cost = float()
    _list = []

    # -- Stage (Get input and write) --

    # Open File for Writing
    output_file = open("inventory.txt", "w")

    # Recieve input for equipment, check if its quit
    equipment = input("Enter name of Equipment: ")
    checkQuitandWriteEquipment(output_file, equipment)
    writeSeperator(output_file)

    # If equipment is not "quit"
    while not equipment == "quit":

        # Recieve data
        num_onhand = input("Number on hand: ")
        cost = input("Cost per item: ")

        # Write data to file
        writeNumOnHand(output_file, num_onhand)
        writeSeperator(output_file)
        writeCost(output_file, cost)
        writeSeperator(output_file)

        # Contiune asking for data
        equipment = input("\nEnter name of Equipment: ")
        checkQuitandWriteEquipment(output_file, equipment)
        writeSeperator(output_file)
    # Close File
    output_file.close()

    # -- Stage (Read and format output) -- #

    # Open File
    input_file = open("inventory.txt", "r")

    # Read file and append contents to _list
    _list = input_file.read().split(",\n")
    _list.pop(-1)  # remove last value from list (extra whitespace)
    _list.pop(-1)
    # Close File
    input_file.close()

    # Make sure "quit" was not the first value (no data entered)
    if not len(_list) == 0:

        # Output Headers
        print("\nIT Inventory")
        print("Name\t\t\tNumber on hand\t\tCost")

        # loop through data and output to user
        for i in range(0, len(_list), 3):
            print("{0:25s}{1:13,d}{2:14.2f}".format(
                _list[i], int(_list[i+1]), float(_list[i+2])))

    # output extra credit
    print("\nTotal value of inventory: ${0:,.2f}".format(computeTotal(_list)))


# Call main
if __name__ == '__main__':
    main()
