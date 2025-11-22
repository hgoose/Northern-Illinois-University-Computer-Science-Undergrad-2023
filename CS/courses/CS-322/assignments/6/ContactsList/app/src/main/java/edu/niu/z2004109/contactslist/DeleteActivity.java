/************************************************************************
 * *
 * CSCI 322/522 Assignment 6 fall 25 *
 * *
 * App Name: Contacts list
 * *
 * Class Name: DeleteActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/16/2025 *
 * *
 * Purpose: Class to handle deleting contacts from the db
 * *
 ************************************************************************/

package edu.niu.z2004109.contactslist;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.GridLayout;
import android.widget.TextView;

import java.util.ArrayList;

public class DeleteActivity extends AppCompatActivity {

    // GridLayout used to display contact data in rows and columns
    private GridLayout layout;

    // Database manager for CRUD operations
    private DBManager dbman;

    // Number of columns per row (first name, last name, email, phone, delete button)
    private static final int COLS = 5;

    // Allow Android to calculate number of rows automatically
    private static final int ROWS = GridLayout.UNDEFINED;

    /**
     * Activity entry point.
     * Creates layout, fills it with DB rows, and adds the Back button.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        dbman = new DBManager(this);     // Initialize DB helper
        createRootLayout();              // Create GridLayout
        fillGrid();                      // Load and display all contacts
        createBackButton();              // Add Back button at bottom
        setContentView(layout);          // Display layout on screen
    }

    /**
     * Creates the Back button and adds it to the bottom of the grid.
     * The button spans all columns.
     */
    private void createBackButton() {
        Button back_button = new Button(this);
        styleButton(back_button, "Back");

        // Clicking Back returns to previous activity
        back_button.setOnClickListener((View v) -> {
            DeleteActivity.this.finish();
        });

        // Layout parameters: place button at next row, spanning all COLS columns
        GridLayout.LayoutParams glp = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED), // next available row
                GridLayout.spec(0, COLS)               // span COLS columns
        );
        glp.width = GridLayout.LayoutParams.MATCH_PARENT;
        glp.height = GridLayout.LayoutParams.MATCH_PARENT;
        glp.setMargins(8,8,8,8);

        back_button.setLayoutParams(glp);
        layout.addView(back_button);
    }

    /**
     * Initializes the GridLayout root container.
     * Sets number of columns and default margins.
     */
    private void createRootLayout() {
        layout = new GridLayout(this);
        layout.setColumnCount(COLS);
        layout.setRowCount(ROWS);

        // Apply top margin so grid is not flush against the top
        ViewGroup.MarginLayoutParams vlp = new ViewGroup.MarginLayoutParams(
                ViewGroup.MarginLayoutParams.MATCH_PARENT,
                ViewGroup.MarginLayoutParams.WRAP_CONTENT
        );
        vlp.setMargins(0,50,0,0);
        layout.setLayoutParams(vlp);
    }

    /**
     * Populates the GridLayout with all rows from the database.
     * Adds a delete button to each row.
     */
    private void fillGrid() {
        createColumnHeaders();  // Add header row at top

        // Load all contacts
        ArrayList<ContactInfo> contacts = dbman.selectAllContacts();

        // For each contact, build a row in the grid
        for (ContactInfo contact : contacts) {

            // Create delete button for this row
            Button button = new Button(this);
            button.setId(contact.getId());                     // Set contact ID as button ID
            styleButton(button, "Delete");

            // Delete from DB and remove row from UI when clicked
            button.setOnClickListener((View v) -> {
                int id = v.getId();
                dbman.delete(id);               // Delete from database
                removeRow((Button) v);           // Delete row from GridLayout
            });

            // Add entire row to grid
            addRow(contact, button);
        }
    }

    /**
     * Adds the header row text labels.
     */
    public void createColumnHeaders() {
        addCell("First Name");
        addCell("Last Name");
        addCell("Email Address");
        addCell("Phone Number");
        addCell("Delete"); // Column header for delete button column
    }

    /**
     * Adds one full row to the grid for a single contact.
     */
    private void addRow(ContactInfo contact, Button button) {
        addCell(contact.getFirstName());
        addCell(contact.getLastName());
        addCell(contact.getEmail());
        addCell(String.valueOf(contact.getNumber()));
        addButton(button);  // Add Delete button
    }

    /**
     * Adds a button to the grid with layout parameters matching other cells.
     */
    private void addButton(Button button) {
        GridLayout.LayoutParams glp = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),           // next row
                GridLayout.spec(GridLayout.UNDEFINED, 1f)        // weighted column
        );
        glp.width = 0;   // width = 0dp + weight = evenly fill column space
        glp.height = GridLayout.LayoutParams.WRAP_CONTENT;
        glp.setMargins(8,8,8,8);
        button.setLayoutParams(glp);

        layout.addView(button);
    }

    /**
     * Adds a text cell (TextView) to the grid.
     */
    private void addCell(String text) {
        TextView tv = new TextView(this);
        tv.setText(text);
        tv.setPadding(16, 16, 16, 16);

        // Weighted layout so columns distribute evenly
        GridLayout.LayoutParams params = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),           // next row
                GridLayout.spec(GridLayout.UNDEFINED, 1f)        // weight = 1
        );
        params.width = 0; // Fill available horizontal space proportionally
        params.height = GridLayout.LayoutParams.WRAP_CONTENT;
        params.setMargins(8, 8, 8, 8);
        tv.setLayoutParams(params);

        layout.addView(tv);
    }

    /**
     * Removes an entire row from the grid when a Delete button is clicked.
     * Each row contains COLS cells (4 TextViews + 1 Delete Button).
     */
    private void removeRow(Button btn) {
        // Get index of button in GridLayout child list
        int btnIndex = layout.indexOfChild(btn);
        if (btnIndex == -1) {
            return; // Should not happen, but safe-guard
        }

        // Determine where the row starts (button is last column in row)
        int rowStartIndex = btnIndex - (COLS - 1);

        // Remove all views belonging to that row
        layout.removeViews(rowStartIndex, COLS);
    }

    /**
     * Sets button text (placeholder for future style expansion).
     */
    private void styleButton(Button button, String message) {
        button.setText(message);
    }
}
