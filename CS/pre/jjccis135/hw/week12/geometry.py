# Driver file for class shape and circle
# I can see that the two circle objects are close in memory

import shape
import circle

shape_object = shape.Shape(12)
circle_object1 = circle.Circle(12, 5)
circle_object2 = circle.Circle(15, 10)

print("The area of the shape is", shape_object.get_area()) # Fill in the blank with the appropriate object name and method call
print("The type of the shape object is", type(shape_object)) # Fill in the blank with the appropriate object name
print("The location in memory of the shape object is", shape_object) # Fill in the blank with the appropriate object name
print()

print("The area of the first circle is", circle_object1.get_area()) # Fill in the blank with the appropriate object name and method call
print("The radius of the first circle is", circle_object1.get_radius()) # Fill in the blank with the appropriate object name and method call
print("The type of the first circle object is", type(circle_object1)) # Fill in the blank with the appropriate object name
print("The location in memory of the first circle object is", circle_object1) # Fill in the blank with the appropriate object name
print()

print("The area of the second circle is", circle_object2.get_area()) # Fill in the blank with the appropriate object name and method call
print("The radius of the second circle is", circle_object2.get_radius()) # Fill in the blank with the appropriate object name and method call
print("The type of the second circle object is", type(circle_object2)) # Fill in the blank with the appropriate object name
print("The location in memory of the first second object is", circle_object2) # Fill in the blank with the appropriate object name


