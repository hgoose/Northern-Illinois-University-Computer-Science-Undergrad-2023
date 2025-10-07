/************************************************************************
 * *
 * CSCI 322/522 Assignment 3 fall 25 *
 * *
 * App Name: Color app *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/06/2025 *
 * *
 * Purpose: Create a simple app to allow the user to set the background of a
 *          TextView label with a custom RGB value
 * *
 ************************************************************************/

package edu.niu.z2004109.colorapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import java.lang.CharSequence;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.TextView;
import android.graphics.Color;

public class MainActivity extends AppCompatActivity {
    RGB color;
    TextView mainLabel;
    EditText inputRed;
    EditText inputBlue;
    EditText inputGreen;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Attach views in view to these java variables
        mainLabel = findViewById(R.id.mainLabel);
        inputRed = findViewById(R.id.EditTextRed);
        inputGreen = findViewById(R.id.EditTextGreen);
        inputBlue = findViewById(R.id.EditTextBlue);

        // Create new color instance
        color = new RGB();

        // Attach listener to first EditText
        inputRed.addTextChangedListener(new TextWatcher() {
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}

            @Override
            public void afterTextChanged(Editable e) {
                // Get value
                String s_red = e.toString();

                // Try to convert to int and update background color
                try {
                    // Convert to int
                    int red = Integer.parseInt(s_red);
                    // Set color in RGB color member
                    color.setRed(red);
                    // Update the background
                    setLabelBackground(color);
                } catch (NumberFormatException nfe) {}
            }
        });

        // Same as above, for green
        inputGreen.addTextChangedListener(new TextWatcher() {
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}

            public void afterTextChanged(Editable e) {
                String s_green = e.toString();
                try {
                    int green = Integer.parseInt(s_green);
                    color.setGreen(green);
                    setLabelBackground(color);
                } catch (NumberFormatException nfe) {}
            }
        });

        // Same as above, for blue
        inputBlue.addTextChangedListener(new TextWatcher() {
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            public void onTextChanged(CharSequence s, int start, int before, int count) {}

            public void afterTextChanged(Editable e) {
                String s_blue = e.toString();
                try {
                    int blue = Integer.parseInt(s_blue);
                    color.setBlue(blue);
                    setLabelBackground(color);
                } catch (NumberFormatException nfe) {}
            }
        });
    }

    // Function to update the background of the Textview label
    void setLabelBackground(RGB rgb) {
        int labelBackgroundColor = Color.rgb(rgb.getRed(), rgb.getGreen(), rgb.getBlue());
        mainLabel.setBackgroundColor(labelBackgroundColor);
    }
}