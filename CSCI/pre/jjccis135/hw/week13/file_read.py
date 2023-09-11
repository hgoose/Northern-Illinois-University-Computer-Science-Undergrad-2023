# Program: Read from file

# Open file
_file = open("data.txt", "r")

# read the entire file into a string
filedata_str = _file.read()

# Close file
_file.close()

# call split function
filedata_list = filedata_str.split(" ")

# Print the resulting list to the screen
print(filedata_list)

#for item in filedata_list:
    #print(item)
