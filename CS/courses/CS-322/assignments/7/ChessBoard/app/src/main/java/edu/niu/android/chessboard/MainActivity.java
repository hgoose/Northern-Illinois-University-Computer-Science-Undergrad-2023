/************************************************************************
 * *
 * CSCI 322/522 Assignment 7 fall 25 *
 * *
 * App Name: Chess Board *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 12/5/2025 *
 * *
 * Purpose: Class to represent model + controller of application
 * *
 ************************************************************************/

package edu.niu.android.chessboard;

import android.content.res.Configuration;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.widget.GridLayout;
import android.graphics.Point;
import android.view.View;
import android.view.ViewGroup;
import android.graphics.Color;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    // Root Layout (GridLayout)
    private BoardView layout;

    // Screen Dims
    int screen_width;
    int screen_height;

    // Colors
    int cell_white;
    int cell_green;
    int piece_white;
    int piece_black;

    // Model member
    String[][] board =  {
            {"R", "K", "B", "Q", "K", "B", "K", "R"},
            {"P", "P", "P", "P", "P", "P", "P", "P"},
            {"", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", ""},
            {"P", "P", "P", "P", "P", "P", "P", "P"},
            {"R", "K", "B", "Q", "K", "B", "K", "R"},
    };

    // Entry
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Set the screen dimensions for the current orientation
        setScreenDimensions();

        // Set the colors
        cell_white = Color.parseColor("#EEEED2");
        cell_green = Color.parseColor("#769656");
        piece_white = Color.parseColor("#F8F8F8");

        // Get the current configuration
        Configuration config = getResources().getConfiguration();

        // Set the black piece color, depending on orientation
        setPieceColors();

        // Create the layout
        layout = new BoardView(this, screen_width,
                screen_height, cell_white,
                cell_green, piece_white,
                piece_black, config.orientation
        );
        layout.createBoard(board);

        // Set the root view
        setContentView(layout);
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        // Set dimensions and black piece color for the new orientation
        setScreenDimensions();
        setPieceColors();

        // Create portrait view
        if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT) {
            layout = new BoardView(this, screen_width,
                    screen_height, cell_white,
                    cell_green, piece_white,
                    piece_black, Configuration.ORIENTATION_PORTRAIT
            );
        // Create landscape view
        } else if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            layout = new BoardView(this, screen_width,
                    screen_height, cell_white,
                    cell_green, piece_white,
                    piece_black, Configuration.ORIENTATION_LANDSCAPE
            );
        }
        // Create the new board
        layout.createBoard(board);
        // Display the root view
        setContentView(layout);
    }

    private void setScreenDimensions() {
        // Create and fill Point object with screen dimensions
        Point p = new Point();
        getWindowManager().getDefaultDisplay().getSize(p);

        // Set the screen dimension members
        screen_width = p.x;
        screen_height = p.y;
    }

    private void setPieceColors() {
        // Get current configuration
        Configuration config = getResources().getConfiguration();

        // In portrait, black pieces are black
        if (config.orientation == Configuration.ORIENTATION_PORTRAIT) {
            piece_black = Color.parseColor("#000000");
        // In landscape, black pieces are red
        } else if (config.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            piece_black = Color.parseColor("#E73536");
        }
    }
}