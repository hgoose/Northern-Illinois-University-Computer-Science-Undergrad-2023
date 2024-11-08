#!/usr/bin/env python3

# Author: Nate Warner
# Date: 10/25
# Class: Cis 135
# Program: Write a program that uses a list to store quiz scores, and then performs statistical analysis on vthe values.

def getQuizScore():
    """ Recieve and return one quizscore """
    return int(input("Enter a Quiz Score: "))

def calculateAverage(_sum, count):
    """ Calculate average of all the quiz grades """    
    return _sum / count        

# Declare Vars
scores_list = [] # List to house scores
user_scores = int() # user input for scores
num_of_scores = int() # Number of scores
scores_sum = int() # sum of scores
scores_average = int() # Average of scores

num_a, num_b, num_c, num_d, num_f = int(), int(), int(), int(), int()

# Prompt how many quiz scores to be entered
num_of_scores = int(input("Enter ammount of quiz scores: ")); print()
    
# Loop to get input for scores, computing sum, and adding scores to list  
counter = int() # Loop counter
while counter < num_of_scores:
    user_scores = getQuizScore()
    scores_sum += user_scores
    scores_list.append(user_scores)

    counter += 1

# Compute average and output
scores_average = float(calculateAverage(scores_sum, num_of_scores))
print("\nAverage Score: {}\n".format(scores_average))

index = int() # Loop index to be updated after each iteration
# Iterate over list of scores and find number of A's-F's 
while index < len(scores_list): 

    # Check each item in list for letter grade and update count variable for each grade
    if (90 <= scores_list[index] <= 100): num_a += 1

    elif (80 <= scores_list[index] <= 89): num_b += 1

    elif (70 <= scores_list[index] <= 79): num_c += 1

    elif (60 <= scores_list[index] <= 69): num_d += 1

    else: num_f += 1

    # Update index
    index += 1 
    
# Output Number of Grades
print("Number of A grades: {}".format(num_a))
print("Number of B grades: {}".format(num_b))
print("Number of C grades: {}".format(num_c))
print("Number of D grades: {}".format(num_d))
print("Number of F grades: {}".format(num_f))
























