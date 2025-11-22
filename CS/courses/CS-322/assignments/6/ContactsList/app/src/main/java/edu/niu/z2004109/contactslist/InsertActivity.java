/************************************************************************
 * *
 * CSCI 322/522 Assignment 6 fall 25 *
 * *
 * App Name: Contacts list
 * *
 * Class Name: InsertActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/16/2025 *
 * *
 * Purpose: Controller + view to handle inserting contacts into the db
 * *
 ************************************************************************/

package edu.niu.z2004109.contactslist;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

/**
 * InsertActivity
 *
 * This activity allows the user to enter information for a new contact
 * (first name, last name, email, and phone number) and insert it into
 * the database. It uses EditText widgets defined in activity_insert.xml.
 */
public class InsertActivity extends AppCompatActivity {

    // Database manager for inserting new rows
    private DBManager dbman;

    // EditText widgets for user input
    private EditText input_first;
    private EditText input_last;
    private EditText input_email;
    private EditText input_number;

    /**
     * Activity creation lifecycle method.
     * Initializes the UI, obtains references to input fields,
     * and creates a DBManager instance.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_insert); // Load XML layout

        dbman = new DBManager(this);                   // Initialize DB helper
        input_first = findViewById(R.id.input_first);  // First name input
        input_last = findViewById(R.id.input_last);    // Last name input
        input_email = findViewById(R.id.input_email);  // Email input
        input_number = findViewById(R.id.input_number);// Phone number input
    }

    /**
     * Called when the user presses the "Insert" button.
     * Reads input values, converts phone number to long, creates
     * a ContactInfo object, and inserts the data into the database.
     */
    public void insertData(View v) {

        // Retrieve text from EditTexts
        String first_name = input_first.getText().toString();
        String last_name = input_last.getText().toString();
        String email = input_email.getText().toString();
        String number_str = input_number.getText().toString();

        // Convert string to long (default to 0 if invalid)
        long number = 0;
        try {
            number = Long.parseLong(number_str);
        } catch(Exception e) {
            System.err.println("Invalid phone number");
        }

        // Create ContactInfo object (id = 0 placeholder, DB autoincrements ID)
        ContactInfo info = new ContactInfo(0, first_name, last_name, email, number);

        // Insert into database
        dbman.insert(info);

        // Clear all input fields after successful insert
        input_first.setText("");
        input_last.setText("");
        input_email.setText("");
        input_number.setText("");
    }

    /**
     * Called when the user presses the "Back" button.
     * Finishes the activity, returning to the previous screen.
     */
    public void goBack(View v){
        this.finish();
    }
}