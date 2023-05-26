# Include class player from player file
import player

# DRIVER

# Declare globals

user_in = str()

user_class = str()
user_level = int()

players_list = []
user_player = object()

# LCV
counter = int()
while counter < 3: # ask user to create 3 players 

	user_in = input("Press D to use default values, or press N to use new values: ").lower()

	# Check if user wants to create default player
	if user_in == "d":
		user_player = player.player()
		

	# User wants to create custom player
	elif user_in == "n":
		user_player = player.player()

		# User enter stats
		user_class = input("Enter a class: ")
		user_level = int(input("Enter a level: "))

		# use set methods to set class members
		user_player.set_class(user_class)
		user_player.set_level(user_level)
	
	
	# Not n or d
	else:
		print("\nInvalid option\n")
		
		
	# append created players to list
	players_list.append(user_player)

	# Update counter
	counter+=1

# Output header
print("\nPlayers: ")

# LCV
index = int()

# Loop over list
while index < len(players_list):
	
	# formatted output for each players class and level
	print("{0:12s}{1:d}".format(players_list[index].get_class(), players_list[index].get_level()))
	
	# Update counter
	index+=1

