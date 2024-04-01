# Example of reading a data file that contains two separators: the new line and the comma
# Each line in the data file is arranged like this:
# Team_nameCommaPlayer_nameCommaPlayer_numberNewline
# Example:
# Hawks,Patrick Kane,88\n
# The data will be printed in neatly aligned columns.

# Create variables
all_data = str()    # string variable to store the contents of the file
all_data_list = []  # list to store the data as one list of lists
player_data = []    # list to store each player's info
player_count = 0    # count of all players (used as loop control variable)

# Open the file for reading
in_file = open("team_data.txt", "r")

# Read all the data in the file into a string variable

all_data = in_file.read()

# Close the data file, since we don';'t need it anymore
in_file.close()

# Split the string variable into a list of player data using the newline as the separator
# all_data_list is now a list of lists (a 2-dimensional list)
all_data_list = all_data.split('\n')

# Print column headings
print("{0:10s}{1:20s}{2:>6s}".format("Team","Player","Number"))
# Loop through the rows in the list.
while player_count < len(all_data_list):
    # Split the current row into a separate player list using the comma as the separator
    player_data = all_data_list[player_count].split(',')
    # Print the contents of the player list
    if not len(player_data) == 1:
        print("{0:10s}{1:20s}{2:>6s}".format(player_data[0], player_data[1], player_data[2]))
    # Update loop control variable
        player_count += 1

    else:
        break

""" (Solution):

I noticed that line 27 splits the data so that each set of data, (team name, player name, player number) is an element of the list all_data_list, then when the loop initiates, it splits that list further so that each set of data is its own list where each element is a piece of data (team name, player name, player number). So we are left with n sets (n being the number of data sets that the user enters) and n + 1 lists for the new line. so as long as the player_data list is greater than 1, it cannot be the list that houses the newline and therefore the loop can procide with its logic for formatting the output)

"""
