/************************************************************************
 * *
 * CSCI 322/522 Assignment 6 fall 25 *
 * *
 * App Name: Contacts list
 * *
 * Class Name: ContactInfo.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/16/2025 *
 * *
 * Purpose: Model to store information about a contact
 * *
 ************************************************************************/

package edu.niu.z2004109.contactslist;

import androidx.annotation.NonNull;

public class ContactInfo {
    // Data members
    private int id;
    private String first_name;
    private String last_name;
    private String email;
    private long number;

    // Parameterized constructor
    public ContactInfo(int id, String first_name, String last_name, String email, long number) {
        setId(id);
        setFirstName(first_name);
        setLastName(last_name);
        setEmail(email);
        setNumber(number);
    }

    // Default constructor
    public ContactInfo() {
        this.id = 0;
        this.first_name = "";
        this.last_name = "";
        this.email = "";
        this.number = 0L;
    }

    // Getters

    public int getId() {
        return id;
    }

    public String getFirstName() {
        return first_name;
    }

    public String getLastName() {
        return last_name;
    }

    public String getEmail() {
        return email;
    }

    public long getNumber() {
        return number;
    }

    public void setId(int id) {
        this.id = id;
    }

    // Setters

    public void setFirstName(String first_name) {
        this.first_name = first_name;
    }

    public void setLastName(String last_name) {
        this.last_name = last_name;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setNumber(long number) {
        this.number = number;
    }

    // To string method
    public String toString() {
        return first_name + ", " + last_name + ", " + email + ", " + number;
    }
}