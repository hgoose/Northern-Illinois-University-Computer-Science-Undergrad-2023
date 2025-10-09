/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Password Validator *
 * *
 * Class Name: PasswordValidator.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/13/2025 *
 * *
 * Purpose: Class to store and validate password.
 *          A strong password is a password with 9 or more characters.
 *          A weak password is a password with fewer than 9 characters.
 * *
 ************************************************************************/
package edu.niu.z2004109.passwordvalidator;

public class PasswordValidator {
    private String password;

    // Parameterized constructor
    PasswordValidator(String password) {
        this.password = password;
    }

    // Default constructor
    PasswordValidator() {
        password = "";
    }

    // Getter
    String getPassword() {
        return password;
    }

    // Setter
    void setPassword(String password) {
        this.password = password;
    }

    // Validate password
    int validate() {
        if (password.length() == 0) {
            return -1;
        } else if (password.length() < 9) {
            return 0;
        } else return 1;
    }
}