#!/usr/bin/env python3

# The two data sets listed below are social media platforms and the year each platform was launched.
# "Facebook", "YouTube", "WhatsApp", "Messenger", "Instagram", "Snapchat", "Reddit", "Twitter", "Skype", "LinkedIn", "Teams", "Discord", "Twitch"
# 2004, 2005, 2009, 2011, 2010, 2011, 2005, 2006, 2003, 2003, 2017, 2015, 2011

# STEP 1 - Build 2 parallel lists using the above two data sets. Don't change the order of the data!
#           Use a meaningful name for each list.
#           Note that the list data might extend far to the right. You can split the list into two
#           lines by pressing enter after a comma.


# STEP 2 - Use a counter-controlled loop to print the values in the list.
#           Use len(your_list_name) in the loop condition.
#           The output must display lik
#           [name of social media platform] was launched in [year that platform was launched].
#           Example output:  Facebook was launched in 2004

platforms = ["Facebook", "YouTube", "WhatsApp", "Messenger", "Instagram", "Snapchat", "Reddit", "Twitter", "Skype", "LinkedIn", "Teams", "Discord", "Twitch"]

platform_years = [2004, 2005, 2009, 2011, 2010, 2011, 2005, 2006, 2003, 2003, 2017, 2015, 2011]

index = 0
while index < len(platforms):
	print("{0:s} was launched in {1:d}".format(platforms[index], platform_years[index]))
	index += 1







