/************************************************************************
 * *
 * CSCI 322/522 Assignment 6 fall 25 *
 * *
 * App Name: Contacts list
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/16/2025 *
 * *
 * Purpose: Controller + view for main activity. Provide menu for different activities,
 *          and list each row in db in GridLayout (embedded in ScrollView)
 * *
 ************************************************************************/

package edu.niu.z2004109.contactslist;

import android.content.Intent;
import android.os.Bundle;
import android.text.InputType;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.GridLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;

/**
 * MainActivity
 *
 * Displays the full contact list inside a scrollable GridLayout.
 * Includes:
 *  - A search bar with AutoComplete suggestions (email filtering)
 *  - Column headers
 *  - A dynamically populated grid of all contacts
 *  - Menu items to navigate to Insert, Delete, and Update activities
 */
public class MainActivity extends AppCompatActivity {

    // Database manager
    private DBManager dbman;

    // Outer scrollable container
    private ScrollView layout;

    // GridLayout used to display rows + columns of data
    private GridLayout contactGrid;

    // Search bar for filtering by email
    private AutoCompleteTextView searchEmail;

    // Stores currently selected filter value (null = no filter)
    private String currentEmailFilter = null;

    /**
     * Activity entry point.
     * Builds UI programmatically (ScrollView + GridLayout + Search bar).
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        dbman = new DBManager(this); // Initialize database helper

        // Create ScrollView parent
        layout = new ScrollView(this);
        ViewGroup.MarginLayoutParams vlp = new ViewGroup.MarginLayoutParams(
                ViewGroup.MarginLayoutParams.MATCH_PARENT,
                ViewGroup.MarginLayoutParams.WRAP_CONTENT
        );
        vlp.setMargins(0,50,0,0); // Top margin
        layout.setLayoutParams(vlp);

        // Create GridLayout container
        contactGrid = new GridLayout(this);
        contactGrid.setColumnCount(4);              // 4 columns (first/last/email/phone)
        contactGrid.setRowCount(GridLayout.UNDEFINED);

        // Add search bar (row 0, spans all 4 columns)
        addSearchBar();

        // Add column header row (row 1)
        createColumnHeaders();

        // Configure autocomplete & search filtering
        setupSearchBar();

        // Display all rows from the database (starting at row 2)
        displayContactGrid(null);

        // Add GridLayout to ScrollView and show UI
        layout.addView(contactGrid);
        setContentView(layout);
    }

    /**
     * Called when returning to this activity.
     * Refreshes suggestions and reloads filtered list.
     */
    @Override
    protected void onResume() {
        super.onResume();
        setupSearchBar();                      // Refresh autocomplete suggestions
        displayContactGrid(currentEmailFilter);// Refresh grid display
    }

    /**
     * Creates the search bar widget and adds it to the grid.
     * Appears in row 0 spanning all columns.
     */
    private void addSearchBar() {
        // Create and set options for search box
        searchEmail = new AutoCompleteTextView(this);
        searchEmail.setHint("Search by email");
        searchEmail.setThreshold(1); // Show autocomplete after 1 character
        searchEmail.setInputType(InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
        searchEmail.setPadding(16, 16, 16, 16);

        // Layout: row 0, span 4 columns
        GridLayout.LayoutParams params = new GridLayout.LayoutParams(
                GridLayout.spec(0),          // row index 0
                GridLayout.spec(0, 4)        // col 0 with span of 4
        );
        // Set param options
        params.width = GridLayout.LayoutParams.MATCH_PARENT;
        params.height = GridLayout.LayoutParams.WRAP_CONTENT;
        params.setMargins(8, 8, 8, 8);
        searchEmail.setLayoutParams(params);

        // Add search box to GridLayout
        contactGrid.addView(searchEmail);
    }

    /**
     * Adds the set of column labels (First / Last / Email / Phone).
     */
    public void createColumnHeaders() {
        addCell("First Name");
        addCell("Last Name");
        addCell("Email Address");
        addCell("Phone Number");
    }

    /**
     * Clears all non-header rows and repopulates the grid
     * based on the provided email filter.
     */
    private void displayContactGrid(String emailFilter) {

        // Grid children:
        // index 0 = search bar
        // index 1–4 = headers
        // index 5+ = data rows
        int childCount = contactGrid.getChildCount();
        if (childCount > 5) {
            // Remove only old data rows, keep search bar + headers
            contactGrid.removeViews(5, childCount - 5);
        }

        // Get all contacts from DB
        ArrayList<ContactInfo> contacts = dbman.selectAllContacts();

        // Add each row that matches the filter
        for (ContactInfo contact : contacts) {

            // If filtering by email, skip non-matching rows
            if (emailFilter != null &&
                    !contact.getEmail().equalsIgnoreCase(emailFilter)) {
                continue;
            }

            // Add contact data to grid
            addCell(contact.getFirstName());
            addCell(contact.getLastName());
            addCell(contact.getEmail());
            addCell(String.valueOf(contact.getNumber()));
        }
    }

    /**
     * Adds one TextView cell to the grid.
     * Used for all headers and data fields.
     */
    private void addCell(String text) {
        TextView tv = new TextView(this);
        tv.setText(text);
        tv.setPadding(16, 16, 16, 16);

        // Weighted layout so all 4 columns share width evenly
        GridLayout.LayoutParams params = new GridLayout.LayoutParams(
                GridLayout.spec(GridLayout.UNDEFINED),          // next row
                GridLayout.spec(GridLayout.UNDEFINED, 1f)       // weight 1
        );
        params.width = 0; // 0dp + weight to evenly distribute columns
        params.height = GridLayout.LayoutParams.WRAP_CONTENT;
        params.setMargins(8, 8, 8, 8);

        tv.setLayoutParams(params);
        contactGrid.addView(tv);
    }

    /**
     * Configures autocomplete behavior and filtering logic for the search bar.
     * Autocomplete suggestions come from all email values in the database.
     */
    private void setupSearchBar() {
        // Retrieve all emails for suggestions
        ArrayList<String> emails = dbman.getAllEmails();

        // Attach ArrayAdapter for dropdown suggestions
        ArrayAdapter<String> emailAdapter = new ArrayAdapter<>(
                this,
                android.R.layout.simple_dropdown_item_1line,
                emails
        );

        searchEmail.setAdapter(emailAdapter);
        searchEmail.setThreshold(1);

        // When user selects an item from dropdown
        searchEmail.setOnItemClickListener((parent, view, position, id) -> {
            String selectedEmail = (String) parent.getItemAtPosition(position);
            currentEmailFilter = selectedEmail;
            displayContactGrid(selectedEmail);     // Show only that row
        });

        // When user types in the search box (live filtering)
        searchEmail.addTextChangedListener(new android.text.TextWatcher() {

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) { }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) { }

            // After each keystroke, re-check the filter
            @Override
            public void afterTextChanged(android.text.Editable s) {
                String text = s.toString().trim();

                if (text.isEmpty()) {
                    // Reset filter → show all contacts
                    currentEmailFilter = null;
                    displayContactGrid(null);
                } else {
                    // Apply partial match filter
                    currentEmailFilter = text;
                    displayContactGrid(text);
                }
            }
        });
    }

    /**
     * Creates the menu (Add, Delete, Update).
     * These menu items appear in the top-right corner.
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    /**
     * Handles clicks on Add/Delete/Update menu items.
     * Each option launches a different activity.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        int id = item.getItemId();

        if (id == R.id.action_add) {
            // Go to Insert screen
            Intent insert_intent = new Intent(this, InsertActivity.class);
            this.startActivity(insert_intent);
            return true;

        } else if (id == R.id.action_delete) {
            // Go to Delete screen
            Intent delete_intent = new Intent(this, DeleteActivity.class);
            this.startActivity(delete_intent);
            return true;

        } else if (id == R.id.action_update) {
            // Go to Update screen
            Intent update_intent = new Intent(this, UpdateActivity.class);
            this.startActivity(update_intent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
