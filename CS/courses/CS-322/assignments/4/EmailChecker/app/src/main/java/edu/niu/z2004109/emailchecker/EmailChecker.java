/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Email Checker *
 * *
 * Class Name: EmailChecker.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/13/2025 *
 * *
 * Purpose: Class to store and validate email address *
 * *
 ************************************************************************/

package edu.niu.z2004109.emailchecker;

import java.util.regex.*;

public class EmailChecker {
    // Data memeber (just an email string)
    String email;

    // Parameterized constructor
    EmailChecker(String email) {
        this.email = email;
    }

    // Default constructor
    EmailChecker() {
        email = "";
    }

    // Sets the email address
    void setEmail(String email) {
        this.email = email;
    }

    // Returns the stored email address
    String getEmail() {
        return email;
    }

    // Validate email address using Regex. All we need is a @ character and a period somewhere after it
    boolean validate() {
        return Pattern.compile(".*@.*\\..*").matcher(email.strip()).matches();
    }
}
