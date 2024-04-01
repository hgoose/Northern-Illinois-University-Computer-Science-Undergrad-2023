# Author: Nate Warner
# Class: CIS 135
# Date: Nov 6

# Program: Write a program that creates player objects that could be used in a role-playing game. Each player object contains a class and a level. Print the players in a neatly formatted list.

# DEFINE CLASS 

class player:
    
    # Members
    m_class = str()
    m_level = int()

    def __init__(self):
        """ Contructor """
        self.m_class = "Knight"
        self.m_level = 1
        
    def set_class(self, _class):
        """ set class """
        self.m_class = _class
        return

    def set_level(self, level):
        """ set level """
        self.m_level = level
        return

    def get_class(self):
        """ return class """
        return self.m_class

    def get_level(self):
        """ return level """
        return self.m_level
    








































