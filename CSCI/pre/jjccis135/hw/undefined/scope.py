#!/usr/bin/env python3

def update_age(age):
    age += 20
    print("age inside the function:", age)

age = 27

print("\nAge before calling update_age =", age)

update_age(age)

print("Age after calling update_age =", age)

