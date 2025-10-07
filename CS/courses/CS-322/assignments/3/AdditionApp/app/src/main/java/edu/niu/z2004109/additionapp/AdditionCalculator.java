/************************************************************************
 * *
 * CSCI 322/522 Assignment 3 fall 25 *
 * *
 * App Name: Addition App *
 * *
 * Class Name: AdditionCalculator.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/06/2025 *
 * *
 * Purpose: Class to store two numbers and find result when added together *
 * *
 ************************************************************************/

package edu.niu.z2004109.additionapp;

public class AdditionCalculator {
    int a;
    int b;

    // Parameterized constructor
    AdditionCalculator(int a, int b) {
        this.a = a;
        this.b = b;
    }

    // Default constructor
    AdditionCalculator() {
        a = 0;
        b = 0;
    }

    // Setters
    void setA(int a) {
        this.a = a;
    }

    void setB(int b) {
        this.b = b;
    }

    // Getters
    int getA() {
        return a;
    }

    int getB() {
        return b;
    }

    // Calculate function
    int calculate() {
        return a + b;
    }
}
