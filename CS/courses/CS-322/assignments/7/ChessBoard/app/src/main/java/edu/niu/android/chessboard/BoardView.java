/************************************************************************
 * *
 * CSCI 322/522 Assignment 7 fall 25 *
 * *
 * App Name: Chess Board *
 * *
 * Class Name: BoardView.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 12/5/2025 *
 * *
 * Purpose: Class to represent view of Application *
 * *
 ************************************************************************/

package edu.niu.android.chessboard;

import android.content.Context;
import android.graphics.Color;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.TextView;
import android.view.Gravity;
import android.graphics.Typeface;
import android.util.TypedValue;
import android.content.res.Configuration;

public class BoardView extends GridLayout {
    // Set numbers of rows and columns
    private static final int ROWS = 8;
    private static final int COLS = 8;

    // Size of a cell and left margin of GridLayout
    int cell_size;
    int margin_left;

    // Colors
    int cell_white;
    int cell_green;
    int piece_white;
    int piece_black;

    // Current context
    Context context;

    // Parameterized Constructor
    public BoardView(Context context, int screen_width,
                     int screen_height, int cell_white,
                     int cell_green, int piece_white,
                     int piece_black, int orientation)
    {
        // Call GridLayout constructor with Context
        super(context);

        // Set the context
        this.context = context;

        // Set cell size and left margin depending on orientation
        if (orientation == Configuration.ORIENTATION_PORTRAIT) {
            cell_size = screen_width / COLS;
            margin_left = 0;
        } else if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
            cell_size = screen_height / ROWS;
            margin_left = screen_width / 2 - (screen_height / 2);
        }

        // Set colors
        this.cell_white = cell_white;
        this.cell_green = cell_green;
        this.piece_white = piece_white;
        this.piece_black = piece_black;

        // Create LayoutParams for root GridLayout
        ViewGroup.MarginLayoutParams glp = new ViewGroup.MarginLayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
        );

        // Set margin
        glp.leftMargin = margin_left;

        // Set row and column counts
        setColumnCount(COLS);
        setRowCount(ROWS);

        // Set params
        setLayoutParams(glp);
    }

    // Creates the chess board
    public void createBoard(String[][] board) {
        // Color flag: True = white square, False = black square
        boolean color_flag = true;

        // Create the 8x8 chess board
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                // Create TextView for current cell
                TextView cell = new TextView(context);
                // Style the cell, if the row greater than 1, we are done with black pieces
                styleCell(cell, board[i][j], color_flag, i > 1);
                // Add the cell to the GridLayout
                addCell(cell, i, j);
                // Flip the flag
                color_flag = !color_flag;
            }
            // Create alternating rows
            color_flag = !color_flag;
        }
    }

    // Function to add TextView to a GridLayout
    private void addCell(TextView tv, int row, int col) {
        // Create LayoutParams for the TextView
        GridLayout.LayoutParams glp = new GridLayout.LayoutParams(
                GridLayout.spec(row), // Row number
                GridLayout.spec(col) // Col number
        );
        // Set size of cell
        glp.width = cell_size;
        glp.height = cell_size;

        // Add to GridLayout
        addView(tv, glp);
    }

    // Function to style cells
    private void styleCell(TextView tv, String text, boolean cell_white, boolean piece_white) {
        // Set text, text position in cell, text size, typeface (bold), cell color, text color, and shadow layer
        tv.setText(text);
        tv.setGravity(Gravity.CENTER);
        tv.setTextSize(TypedValue.COMPLEX_UNIT_SP, 20);
        tv.setTypeface(null, Typeface.BOLD);
        tv.setBackgroundColor(cell_white ? this.cell_white : this.cell_green);
        tv.setTextColor(piece_white ? this.piece_white : this.piece_black);
        tv.setShadowLayer(3f, 0, 0, Color.BLACK);
    }
}
