# Author: Nate Warner
# Class: CIS 135
# Date: 11/19/22
# Program: Write a program that handles IT equipment inventory by writing to and reading from a plain text file.

""" 
// TODO:
    1: Handle ints and floats instead of strings
    2: Refactor
    3: extra credit
    4: Comments

"""



equipment = str()
num_onhand = str()
cost = str()


def seperator(file):
    file.write(",\n")


output_file = open("inventory.txt", "w")

def getInput_Write():
    equipment = input("Enter name of Equipment: ")
    output_file.write(equipment)
    seperator(output_file)

    while equipment != "quit":

        num_onhand = input("Number on hand: ")
        cost = input("Cost per item: ")

        output_file.writelines(num_onhand)
        seperator(output_file)

        output_file.writelines(cost)
        seperator(output_file)

        equipment = input("\nEnter name of Equipment: ")
        if equipment != "quit":

            output_file.writelines(equipment)
            seperator(output_file)

    output_file.close()

def read():

    input_file = open("inventory.txt", "r")
    _list = input_file.read().split(",\n")
    _list.pop(-1)

    print("\nIT Inventory")
    print("Name\t\t\tNumber on hand\t\tCost")


    index = int()
    if len(_list) == 3:
        print("{0:37s}{1:14s}{2:s}".format(_list[0], _list[1], _list[2]))

    else:
        for i in range(int(len(_list) / 3)):
            print("{0:20s}{1:d}{2:.2f}".format(_list[index], _list[index+1], _list[index+2]))
              
    
    

def main():
    getInput_Write()
    read()
    

if __name__ == '__main__':
    main()


