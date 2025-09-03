/************************************************************************
 * *
 * CSCI 322/522 Assignment 1 fall 25 *
 * *
 * App Name: This Is Fun *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 09/03/2025 *
 * *
 * Purpose: Create a simple app that displays the text This Is Fun! in the top
 *          left of the screen with no margin. Make the app run in horizontal orientation*
 * *
 ************************************************************************/
package edu.niu.z2004109.A1b;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}