# STEP 1 - Write the statement that will allow this driver file to use the car class
import Week11_car_def_file
# STEP 2 - Instantiate an object of the Car class, using the syntax below:
#           variable name for this object = file name.class name()
#           Within the parentheses, you must provide two arguments. (Remember that
#           Arguments are Actual data.) It is ok to hard-code values here. These values
#           must be listed in the correct order. (Refer to the constructor for the correct order.)
car1 = Week11_car_def_file.Car(100, "purple")
# STEP 3 - Complete the print statement below. You will have to add two things to the parentheses
#           of the format function:
#           1. The first argument in the format () refers to the color of the car. CALL THE APPROPRIATE
#               GET METHOD HERE. DO NOT ACCESS THE CLASS VARIABLE DIRECTLY.
#           2. The second argument in the format () refers to the mileage. CALL THE APPROPRIATE
#               GET METHOD HERE. DO NOT ACCESS THE CLASS VARIABLE DIRECTLY.
print("My car is {0:s} and it has {1:d} miles.".format(car1.get_color(), car1.get_mileage()))

# STEP 4 - Update the color by calling the appropriate SET METHOD. DO NOT ACCESS THE CLASS VARIABLE DIRECTLY.
#           It's ok to hard-code a color here.
car1.set_color("blue")
# STEP 5 - Update the mileage by calling the appropriate SET METHOD. DO NOT ACCESS THE CLASS VARIABLE DIRECTLY.
#           It's ok to hard-code a mileage value here.
car1.set_mileage(200)

# STEP 6 - Copy the print statement from STEP 3.
print("My car is {0:s} and it has {1:d} miles.".format(car1.get_color(), car1.get_mileage()))
