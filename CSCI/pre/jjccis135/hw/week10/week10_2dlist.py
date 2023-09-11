#!/usr/bin/env python3

# In this lab, you will be displaying the contents of the 2-dimensional list below.
# NOTE 1 - In the instructions for printing, the data is displayed on one line, just
# to save space in this file. Your output will display with one number per line, and that is ok!
# NOTE 2 - Remember that a loop control variable (aka an index) can be updated by adding to it
#    or by subtracting from it.
# NOTE 3 - BE careful about indenting within the loops.

# Use the following two-dimensional list for this lab:
num_list =  [
            [14, 20, 17, 6, 81, 13],
            [12, 35, 8, 11, 29, 15],
            [5, 19, 58, 47, 95, 86],
            [3, 4, 22, 88, 1, 18]
            ]

# STEP 1 - Assign the appropriate values to these variables:
num_of_rows = len(num_list)-1
num_of_cols = len(num_list[0])-1

print("Data in original order:")
# Use NESTED WHILE LOOPS to print the data in the list in the order shown below.
# Use the variables created above.
# Note there should not be a comma between these values.
# 14 20 17 6 81 13 12 35 8 11 29 15 5 19 58 47 95 86 3 4 22 88 1 18

# STEP 2 - Assign the appropriate starting value to this loop control variable:
row_index = 0

# STEP 3 - Create the loop condition for the outer loop
while row_index <= num_of_rows:
    # STEP 4 - Assign the appropriate starting value to this loop control variable:
    col_index = 0
    # STEP 5 - Create the loop condition for the inner loop
    while  col_index <= num_of_cols:
        # STEP 6 - Print the appropriate element in the list.
        # Remember you need TWO indexes to refer to an element in the list.
        print(num_list[row_index][col_index])
        # STEP 7 - Write the statement that updates the LCV of the inner loop
        col_index += 1
    # STEP 8 - Write the statement that updates the LCV of the outer loop
    row_index += 1

print()
print("Data in opposite order:")
# Use NESTED WHILE LOOPS to print the data in the opposite order.
# Use the same variables you used above.
# Note there should not be a comma between these values.
# 18 1 88 22 4 3 86 95 47 58 19 5 15 29 11 8 35 12 13 81 6 17 20 14

# STEP 9 - Assign the appropriate starting value to this loop control variable:
#   Remember! We're starting from the end! (What is the last valid index for
#   each row?
row_index = num_of_rows

# STEP 10 - Create the loop condition for the outer loop
while row_index >= 0:
    # STEP 11 - Assign the appropriate starting value to this loop control variable:
    #   Remember! We're starting from the end! (What is the last valid index for
    #   each column?
    col_index = num_of_cols
    # STEP 12 - Create the loop condition for the inner loop
    while col_index >= 0:
        # STEP 13 - Print the appropriate element in the list.
        # Remember you need TWO indexes to refer to an element in the list.
        print(num_list[row_index][col_index])
        # STEP 14 - Write the statement that updates the LCV of the inner loop
        col_index -= 1
    # STEP 15 - Write the statement that updates the LCV of the outer loop
    row_index -= 1
