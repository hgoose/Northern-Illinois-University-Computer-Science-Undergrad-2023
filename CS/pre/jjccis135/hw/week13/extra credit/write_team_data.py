# Example of writing to a data file that contains two separators:
# the new line and the comma
# Each line in the data file is arranged like this:
# Team_nameCommaPlayer_nameCommaPlayer_numberNewline
# Example:
# Hawks,Patrick Kane,88\n

# Open the file for writing:
output_file = open("team_data.txt", "w")

# Write data using a loop.
# Prompt for team name (which is loop control variable)
team_name = input("Enter a team name (type quit to exit): ")
# As long as team is not quit
while not team_name.lower() == "quit":
    # Write team name to file
    output_file.write(team_name)
    # Write comma to file, which is separator between player data
    output_file.write(',')
    # Prompt for player name
    player_name = input("Enter a player name: ")
    # Write player name to file
    output_file.write(player_name)
    # Write comma to file, which is separator between player data
    output_file.write(',')
    # Prompt for player number
    player_number = input("Enter a player number: ")
    # Write player number to file
    output_file.write(player_number)
    # Write newline to file, which is separator between rows of player data
    output_file.write('\n')
    # Prompt for team name (which is loop control variable)
    team_name = input("Enter a team name (type quit to exit): ")

# Step 3 - Close the file
output_file.close()
