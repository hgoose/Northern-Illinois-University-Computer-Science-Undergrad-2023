/************************************************************************
 * *
 * CSCI 322/522 Assignment 1 fall 25 *
 * *
 * App Name: I Like Android *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 09/03/2025 *
 * *
 * Purpose: Create a simple app that displays the text I Like Android *
 * *
 ************************************************************************/

package edu.niu.z2004109.A1a;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}