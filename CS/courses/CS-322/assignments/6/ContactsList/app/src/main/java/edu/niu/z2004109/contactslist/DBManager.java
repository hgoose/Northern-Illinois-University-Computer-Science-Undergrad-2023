/************************************************************************
 * *
 * CSCI 322/522 Assignment 6 fall 25 *
 * *
 * App Name: Contacts list
 * *
 * Class Name: DBManager.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/16/2025 *
 * *
 * Purpose: Class to manage database
 * *
 ************************************************************************/

package edu.niu.z2004109.contactslist;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import java.util.ArrayList;

public class DBManager extends SQLiteOpenHelper {

    // ---------------------------------------------------------------------
    // Class Constants
    // ---------------------------------------------------------------------

    // Name of the SQLite database file
    private static final String DATABASE_NAME = "contactsDB";

    // Version number of the database (used for upgrades)
    private static final int DATABASE_VERSION = 1;

    // Table name
    private static final String TABLE_CONTACTS = "contacts";

    // Column names
    private static final String ID = "id";
    private static final String FIRSTNAME = "first_name";
    private static final String LASTNAME = "last_name";
    private static final String EMAIL = "email";
    private static final String NUMBER = "number";

    // ---------------------------------------------------------------------
    // Constructor
    // ---------------------------------------------------------------------
    public DBManager(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // ---------------------------------------------------------------------
    // Database Creation
    // ---------------------------------------------------------------------
    @Override
    public void onCreate(SQLiteDatabase db) {
        // Build SQL CREATE TABLE statement
        String sqlCreate = "create table " + TABLE_CONTACTS + "(" + ID;
        sqlCreate += " integer primary key autoincrement, " + FIRSTNAME;
        sqlCreate += " text, " + LASTNAME + " text," + EMAIL;
        sqlCreate += " text, " + NUMBER + " text)" ;

        // Execute CREATE TABLE
        db.execSQL(sqlCreate);
    }

    // ---------------------------------------------------------------------
    // Database Upgrade
    // ---------------------------------------------------------------------
    @Override
    public void onUpgrade(SQLiteDatabase db, int v_old, int v_new) {
        // Drop old table if it exists
        db.execSQL("drop table if exists " + TABLE_CONTACTS);

        // Recreate table
        onCreate(db);
    }

    // ---------------------------------------------------------------------
    // Insert Operation
    // ---------------------------------------------------------------------
    public void insert(ContactInfo info) {
        // Open DB for writing
        SQLiteDatabase db = getWritableDatabase();

        // Build INSERT statement
        String query = "INSERT INTO " + TABLE_CONTACTS + " " +
                "(first_name, last_name, email, number) VALUES (" +
                "'" + info.getFirstName() + "', " +
                "'" + info.getLastName() + "', " +
                "'" + info.getEmail() + "', " +
                "'" + info.getNumber() + "')" ;

        // Execute insert
        db.execSQL(query);

        // Close DB
        db.close();
    }

    // ---------------------------------------------------------------------
    // Select All Contacts
    // ---------------------------------------------------------------------
    public ArrayList<ContactInfo> selectAllContacts() {
        // List to hold all contacts
        ArrayList<ContactInfo> contacts = new ArrayList<>();

        // Open DB for reading
        SQLiteDatabase db = getReadableDatabase();

        // SQL query to select all rows
        String query = "SELECT * FROM " + TABLE_CONTACTS;

        // Cursor to iterate through result set
        Cursor cursor = db.rawQuery(query, null);

        // Iterate through each row returned
        while (cursor.moveToNext()) {

            // Build ContactInfo object from cursor data
            ContactInfo info = new ContactInfo(
                    Integer.parseInt(cursor.getString(0)), // id
                    cursor.getString(1),                  // first_name
                    cursor.getString(2),                  // last_name
                    cursor.getString(3),                  // email
                    Long.parseLong(cursor.getString(4))   // number
            );

            // Add to list
            contacts.add(info);
        }

        // Close cursor and DB
        cursor.close();
        db.close();

        // Return list of all contacts
        return contacts;
    }

    // ---------------------------------------------------------------------
    // Select All Emails
    // ---------------------------------------------------------------------
    public ArrayList<String> getAllEmails() {
        ArrayList<String> emails = new ArrayList<>();

        // Open DB for reading
        SQLiteDatabase db = getReadableDatabase();

        // Query for just the email column
        String query = "SELECT " + EMAIL + " FROM " + TABLE_CONTACTS;

        // Execute query
        Cursor cursor = db.rawQuery(query, null);

        // Extract emails from rows
        while (cursor.moveToNext()) {
            emails.add(cursor.getString(0));
        }

        // Close cursor and DB
        cursor.close();
        db.close();

        // Return list of emails
        return emails;
    }

    // ---------------------------------------------------------------------
    // Update Operation
    // ---------------------------------------------------------------------
    public void update(ContactInfo info) {
        // Open DB
        SQLiteDatabase db = getWritableDatabase();

        // Build UPDATE statement
        String query = "UPDATE " + TABLE_CONTACTS + " SET " +
                FIRSTNAME + " = '" + info.getFirstName() + "', " +
                LASTNAME + " = '" + info.getLastName() + "', " +
                EMAIL   + " = '" + info.getEmail() + "', " +
                NUMBER  + " = '" + info.getNumber() + "' " +
                "WHERE " + ID + " = " + info.getId();

        // Execute update
        db.execSQL(query);

        // Close DB
        db.close();
    }

    // ---------------------------------------------------------------------
    // Delete Operation
    // ---------------------------------------------------------------------
    public void delete(int id) {
        // Open DB for writing
        SQLiteDatabase db = getReadableDatabase();

        // Build DELETE statement
        String query = "DELETE FROM " + TABLE_CONTACTS + " WHERE id=" + id;

        // Execute delete
        db.execSQL(query);

        // Close DB
        db.close();
    }
}