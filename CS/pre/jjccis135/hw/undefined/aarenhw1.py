#!/usr/bin/env/python3
import os
import sys

def FindSeason():
	
		month = str(input("Enter Month: ")).lower()
		day = int(input("Enter the day: "))
		
		spring = ["march", "april", "may", "june"]
		summer = ["june", "july", "august", "september"]
		autumn = ["september", "october", "november", "december"]
		winter = ["december", "january", "march"]

		returnSpring = "season is spring"
		returnSummer = "season is summer"
		returnAutumn = "season is autumn"
		returnWinter = "season is winter"
		
		if month in spring:
			if month == "march":
				if day >= 20:
					print(returnSpring)
			elif month == "june":
				if day <= 20:
					print(returnSpring)
			else:
				print(returnSpring)
		
		if month in summer:
			if month == "june":
				if day >= 21:
					print(returnSummer)
			elif month == "september":
				if day <= 21:
					print(returnSummer)
			else:
				print(returnSummer)
		
		if month in autumn:
			if month == "september":
				if day >= 22:
					print(returnAutumn)
			elif month == "december":
				if day <= 20:
					print(returnAutumn)
			else:
				print(returnAutumn)

		if month in winter:
			if month == "december":
				if day >= 21:
					print(returnWinter)
			elif month == "march":	
				if day <= 19:
					print(returnWinter)
			else:
				print(returnWinter) 
		
def main():

	if sys.platform == "windows":
		os.system("cls")
	if sys.platform == "linux":
		os.system("clear")
	
	FindSeason()
		
	return 0;
	

if __name__ == '__main__':
	main()
