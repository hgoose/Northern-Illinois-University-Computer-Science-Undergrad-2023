# This file will contain the class definition for a class called Car.

# STEP 1: Write the statement that is required at the beginning of a class definition.
#           Remember that all statements that follow must be indented.
class Car:

# STEP 2: Create TWO variables that will represent two attributes of a car.
#           1) An integer that will represent the mileage
#           2) A string that will represent the color.
#           Declare these variables using this syntax:
#                   the variable name you use = int()
#                   the variable name you use = str()
    m_mileage = int()
    m_color = str()
# STEP 3: Create a set method below that updates the integer class variable declared in Step 2 above.
#           The method name must use this naming convention:  set_nameofvariable
#           This method requires two parameters:
#               1) self will be added automatically. Don't delete it!
#               2) A parameter that will be used to set the value of the integer class variable
#                   from Step 2.
#           Within the method, create an assignment statement, using this syntax:
#               self.nameofvariable = nameofparameter
#           Add the return keyword at the end of the method.
    def set_mileage(self, mileage):
        self.m_mileage = mileage
        return
# STEP 4: Create a set method below that updates the string class variable declared in Step 2 above.
#           The method name must use this naming convention:  set_nameofvariable
#           This method requires two parameters:
#               1) self will be added automatically. Don't delete it!
#               2) A parameter that will be used to set the value of the string class variable
#                   from Step 2.
#           Within the method, create an assignment statement, using this syntax:
#               self.nameofvariable = nameofparameter
#           Add the return keyword at the end of the method.
    def set_color(self, color):
        self.m_color = color
        return
# STEP 5: Create a get method below that returns the value of the integer class variable
#           declared in Step 2 above.
#           The method name must use this naming convention:  get_nameofvariable
#           This method requires one parameter - self, which will be added automatically. Don't delete it!
#           Within the method, return the integer class variable declared in Step 2.
    def get_mileage(self):
        return self.m_mileage
# STEP 6: Create a get method below that returns the value of the string class variable
#           declared in Step 2 above.
#           The method name must use this naming convention:  get_nameofvariable
#           This method requires one parameter - self, which will be added automatically. Don't delete it!
#           Within the method, return the string class variable declared in Step 2.
    def get_color(self):
        return self.m_color
# STEP 7: Complete the constructor below.
#           1. Complete the first line of the constructor, by adding two parameters
#               to the parameter list. The two parameters will be used to set the values
#               of the class variables you created in Step 2. The first parameter will be
#               used to update the integer class variable. The second parameter will be
#               used to update the string class variable.
#           2. Within the constructor, use each parameter to call the corresponding set
#               method declared in Steps 3 & 4 above.
    def __init__(self, mileage, color):
        self.set_mileage(mileage)
        self.set_color(color)
        return
