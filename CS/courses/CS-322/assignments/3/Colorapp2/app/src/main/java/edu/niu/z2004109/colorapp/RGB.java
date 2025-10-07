/************************************************************************
 * *
 * CSCI 322/522 Assignment 3 fall 25 *
 * *
 * App Name: Color app *
 * *
 * Class Name: RGB.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/06/2025 *
 * *
 * Purpose: Class to represent an RGB value as a 3-tuple (red, green, blue),
 *          has functionality to set and validate each value
 * *
 ************************************************************************/

package edu.niu.z2004109.colorapp;

public class RGB {
    // Individual colors
    private int red;
    private int blue;
    private int green;

    // Validate each color. Must be at least zero and at most 255
    static int validate(int color) {
        // If the color is less than zero, return 0
        if (color < 0) {
            return 0;

            // If the color is greater than 255, return 255
        } else if (color > 255) {
            return 255;
        }
        // Else, the color is valid
        else return color;
    }

    // Parameterized constructor
    RGB(int red, int blue, int green) {
        this.red = validate(red);
        this.blue = validate(blue);
        this.green = validate(green);
    }

    // Default constructor
    RGB() {
        this.red = 0;
        this.blue = 0;
        this.green = 0;
    }

    // Setters
    void setRed(int red) {
       this.red = validate(red);
    }

    void setBlue(int blue) {
        this.blue = validate(blue);
    }

    void setGreen(int green) {
        this.green = validate(green);
    }

    // Getters
    int getRed() {
        return red;
    }

    int getBlue() {
        return blue;
    }

    int getGreen() {
        return green;
    }
}
