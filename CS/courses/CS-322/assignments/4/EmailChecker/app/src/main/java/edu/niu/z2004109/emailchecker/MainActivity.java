/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Email Checker *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/13/2025 *
 * *
 * Purpose: Create an app to validate emails *
 * *
 ************************************************************************/
package edu.niu.z2004109.emailchecker;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Button;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.constraintlayout.widget.ConstraintSet;
import android.view.ViewGroup;
import android.view.View;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.view.Gravity;

public class MainActivity extends AppCompatActivity {
    EmailChecker checker;
    ConstraintLayout layout;
    TextView label;
    EditText input;
    Button check;

    // Custom colors
    static final int GRAY = Color.parseColor("#C2C2C2");
    static final int PURPLE = Color.parseColor("#FF0FC3");
    static final int RED = Color.parseColor("#FF2A00");
    static final int GREEN = Color.parseColor("#00FF33");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Email checker instance
        checker = new EmailChecker();

        // Create ConstraintLayout (root view) and set layout params
        layout = new ConstraintLayout(this);
        layout.setLayoutParams(
                new ViewGroup.LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT,
                        ViewGroup.LayoutParams.MATCH_PARENT
                )
        );

        // Create label, input, and submit button
        label = new TextView(this);
        input = new EditText(this);
        check = new Button(this);

        // Label settings
        setLabelStyle(label, GRAY);

        // Input settings
        setInputStyle(input, "Enter Email Address");

        // Check button settings
        setButtonStyle(check, "Check");

        // Set layout params for children
        setChildrenLayoutParams(label, 400, 150, 0.3f);
        setChildrenLayoutParams(input,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                0.4f
        );
        setChildrenLayoutParams(check,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                0.5f
        );

        // Add children to parent
        layout.addView(label);
        layout.addView(input);
        layout.addView(check);

        // Event listeners
        check.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                checker.setEmail(input.getText().toString());
                if (checker.validate()) {
                    setLabelStatus(label, "VALID", GREEN);
                } else {
                    setLabelStatus(label, "INVALID", RED);
                }
            }
        });

        // Set the content view as the ConstraintLayout
        setContentView(layout);
    }

    // Applies ConstraintLayout layout parameters for children of root view
    void setChildrenLayoutParams(View v, int width, int height, float vbias) {
        ConstraintLayout.LayoutParams  lp = new ConstraintLayout.LayoutParams(
                width, height
        );
        lp.bottomToBottom = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.endToEnd = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.startToStart = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.topToTop = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.verticalBias = vbias;

        v.setLayoutParams(lp);
    }

    // Sets text and color of TextView
    void setLabelStatus(TextView v, String message, int color) {
        v.setText(message);
        label.setBackgroundColor(color);
    }

    // Sets the style for buttons
    void setButtonStyle(Button b, String message) {
        // Create shape for button
        GradientDrawable button_shape = new GradientDrawable();
        button_shape.setShape(GradientDrawable.RECTANGLE);
        button_shape.setCornerRadius(35f);
        button_shape.setColor(PURPLE);

        // Set properties
        b.setText(message);
        b.setBackground(button_shape);
        b.setTextSize(25);
        b.setPadding(100,20,100,20);
        b.setGravity(Gravity.CENTER);
    }

    // Sets the style for labels
    void setLabelStyle(TextView tv, int color) {
        // Set properties for TextView label
        tv.setBackgroundColor(color);
        tv.setPadding(100,20,100,20);
        tv.setGravity(Gravity.CENTER);
        tv.setPadding(100,20,100,20);
    }

    // Sets the style for inputs
    void setInputStyle(EditText et, String message) {
        // Properties for EditText
        input.setHint(message);
        input.setGravity(Gravity.CENTER);
        input.setTextSize(25);
        input.setPadding(100,20,100,20);
    }
}