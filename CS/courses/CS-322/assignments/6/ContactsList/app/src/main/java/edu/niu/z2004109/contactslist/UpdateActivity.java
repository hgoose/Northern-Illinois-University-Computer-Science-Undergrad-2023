/************************************************************************
 * *
 * CSCI 322/522 Assignment 6 fall 25 *
 * *
 * App Name: Contacts list
 * *
 * Class Name: UpdateActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/16/2025 *
 * *
 * Purpose: Contoller + view to handle updating contacts in db
 * *
 ************************************************************************/

package edu.niu.z2004109.contactslist;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridLayout;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * UpdateActivity
 *
 * Displays all contacts in a GridLayout where each row contains editable
 * EditText fields (first name, last name, email, phone), along with an
 * Update button. When pressed, the Update button writes the modified
 * values back to the database.
 */
public class UpdateActivity extends AppCompatActivity {

    // GridLayout container for displaying editable contact rows
    private GridLayout layout;

    // Database manager for retrieving and updating data
    private DBManager dbman;

    // Number of columns per row: 4 fields + 1 Update button
    private static final int COLS = 5;

    // Let GridLayout determine number of rows automatically
    private static final int ROWS = GridLayout.UNDEFINED;

    /**
     * Activity entry point.
     * Creates layout, loads contacts, and adds Back button.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        dbman = new DBManager(this); // Initialize DB helper

        createRootLayout();  // Set up GridLayout formatting
        fillGrid();          // Populate grid with editable rows
        createBackButton();  // Add Back button at end

        setContentView(layout);
    }

    /**
     * Creates the GridLayout root container with margins and column count.
     */
    private void createRootLayout() {
        // Create GridLayout and set rows and cols
        layout = new GridLayout(this);
        layout.setColumnCount(COLS);
        layout.setRowCount(ROWS);

        // Apply top margin to the entire GridLayout
        ViewGroup.MarginLayoutParams vlp = new ViewGroup.MarginLayoutParams(
                ViewGroup.MarginLayoutParams.MATCH_PARENT,
                ViewGroup.MarginLayoutParams.WRAP_CONTENT
        );
        vlp.setMargins(0, 50, 0, 0);
        layout.setLayoutParams(vlp);
    }

    /**
     * Reads all contacts from the database and creates an editable row
     * for each one.
     */
    private void fillGrid() {
        createColumnHeaders();

        // Retrieve all contacts from the database
        ArrayList<ContactInfo> contacts = dbman.selectAllContacts();

        // Build a row for each contact
        for (ContactInfo contact : contacts) {
            addRow(contact);
        }
    }

    /**
     * Adds the header row for the editable grid.
     */
    private void createColumnHeaders() {
        addHeaderCell("First Name");
        addHeaderCell("Last Name");
        addHeaderCell("Email Address");
        addHeaderCell("Phone Number");
        addHeaderCell("Update");
    }

    /**
     * Creates one editable row containing:
     *  - First name EditText
     *  - Last name EditText
     *  - Email EditText
     *  - Phone EditText
     *  - Update button
     */
    private void addRow(ContactInfo contact) {

        // Editable text fields pre-filled with existing data
        EditText etFirst = addEditCell(contact.getFirstName());
        EditText etLast  = addEditCell(contact.getLastName());
        EditText etEmail = addEditCell(contact.getEmail());
        EditText etNum   = addEditCell(String.valueOf(contact.getNumber()));

        // Create Update button
        Button updateButton = new Button(this);
        styleButton(updateButton, "Update");

        // Bundle all EditTexts + ID so the click listener can retrieve row data
        RowViews row = new RowViews(
                contact.getId(),
                etFirst,
                etLast,
                etEmail,
                etNum
        );
        updateButton.setTag(row);

        // When Update button is clicked, retrieve new values and update DB
        updateButton.setOnClickListener(v -> {
            RowViews r = (RowViews) v.getTag();

            // Read edited text
            String newFirst = r.first.getText().toString().trim();
            String newLast  = r.last.getText().toString().trim();
            String newEmail = r.email.getText().toString().trim();
            String numStr   = r.number.getText().toString().trim();

            // Convert phone number string to long
            long newNumber = 0L;
            try {
                newNumber = Long.parseLong(numStr);
            } catch (Exception e) {
                System.err.println("Invalid phone number: " + numStr);
            }

            // Create updated ContactInfo object
            ContactInfo updated = new ContactInfo(
                    r.id, newFirst, newLast, newEmail, newNumber
            );

            // Perform database update
            dbman.update(updated);
        });

        // Add Update button to grid
        addButtonCell(updateButton);
    }

    /**
     * Adds a header cell TextView (used for top header row).
     */
    private void addHeaderCell(String text) {
        TextView tv = new TextView(this);
        tv.setText(text);
        tv.setPadding(16, 16, 16, 16);
        tv.setTextSize(16);
        tv.setAllCaps(false);

        // Weighted layout to evenly distribute columns
        GridLayout.LayoutParams params = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),
                GridLayout.spec(GridLayout.UNDEFINED, 1f)
        );
        params.width = 0;   // 0dp + weight = equal column width
        params.height = GridLayout.LayoutParams.WRAP_CONTENT;
        params.setMargins(8, 8, 8, 8);
        tv.setLayoutParams(params);

        layout.addView(tv);
    }

    /**
     * Creates an EditText populated with the given text and adds it to the grid.
     *
     * @param text Initial value to place into the EditText
     * @return reference to created EditText (so row can retrieve input later)
     */
    private EditText addEditCell(String text) {
        EditText et = new EditText(this);
        et.setText(text);
        et.setPadding(16, 16, 16, 16);

        // Equal-width columns using weight system
        GridLayout.LayoutParams params = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),
                GridLayout.spec(GridLayout.UNDEFINED, 1f)
        );
        params.width = 0; // Fill available width using weight
        params.height = GridLayout.LayoutParams.WRAP_CONTENT;
        params.setMargins(8, 8, 8, 8);
        et.setLayoutParams(params);

        layout.addView(et);
        return et;
    }

    /**
     * Adds a button cell to the row (this is the "Update" button).
     */
    private void addButtonCell(Button button) {
        // Set LayoutParams for the button
        GridLayout.LayoutParams glp = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),
                GridLayout.spec(GridLayout.UNDEFINED, 1f)
        );
        // Set param options
        glp.width = 0;
        glp.height = GridLayout.LayoutParams.WRAP_CONTENT;
        glp.setMargins(8, 8, 8, 8);
        button.setLayoutParams(glp);

        // Add button to GridLayout
        layout.addView(button);
    }

    /**
     * Adds a Back button at the bottom of the layout.
     * The Back button spans all columns.
     */
    private void createBackButton() {
        // Create button
        Button back_button = new Button(this);
        // Style the button
        styleButton(back_button, "Back");

        // Finish activity when Back is clicked
        back_button.setOnClickListener(v -> UpdateActivity.this.finish());

        // Back button spans all COLS columns
        GridLayout.LayoutParams glp = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED), // next row index
                GridLayout.spec(0, COLS)               // span full width
        );
        // Set Layout params
        glp.width = GridLayout.LayoutParams.MATCH_PARENT;
        glp.height = GridLayout.LayoutParams.WRAP_CONTENT;
        glp.setMargins(8, 8, 8, 8);
        back_button.setLayoutParams(glp);

        // Add back button to GridLayout
        layout.addView(back_button);
    }

    /**
     * Basic button styling helper (currently only sets text).
     */
    private void styleButton(Button button, String message) {
        button.setText(message);
    }

    /**
     * Helper class used to store references to the EditTexts and the ID
     * associated with a single row in the grid. Each Update button stores
     * one RowViews object using setTag().
     */
    private static class RowViews {
        int id;
        EditText first;
        EditText last;
        EditText email;
        EditText number;

        RowViews(int id, EditText first, EditText last,
                 EditText email, EditText number) {
            this.id = id;
            this.first = first;
            this.last = last;
            this.email = email;
            this.number = number;
        }
    }
}