
/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Password Validator *
 * *
 * Class Name: PasswordValidatorView.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/13/2025 *
 * *
 * Purpose: View class of the application
 * *
 ************************************************************************/
package edu.niu.z2004109.passwordvalidator;

import androidx.constraintlayout.widget.ConstraintLayout;
import android.widget.TextView;
import android.widget.EditText;
import android.view.View;
import android.view.ViewGroup;
import android.text.TextWatcher;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.graphics.Typeface;
import android.content.Context;

public class PasswordValidatorView extends ConstraintLayout {

    // Widget members
    EditText input;
    TextView label;

    // Define custom colors
    protected static final int YELLOW = Color.parseColor("#FFFFA3");
    protected static final int OLIVE = Color.parseColor("#72AD49");
    protected static final int BROWN = Color.parseColor("#857756");
    protected static final int GREEN = Color.parseColor("#57FF95");
    protected static final int RED = Color.parseColor("#FF5757");

    // Constructor
    PasswordValidatorView(Context context, int w, int h, TextWatcher tch) {
        // Create ConstraintLayout (root view)
        super(context);

        // Set the layout params
        setLayoutParams(new ViewGroup.LayoutParams(
                w,h
        ));
        // Set the background color
        setBackgroundColor(YELLOW);

        // Create the label and the EditText
        label = new TextView(context);
        input = new EditText(context);

        // Set the layout params for the label and EditText
        setChildrenLayoutParams(label,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                0.6f
        );

        setChildrenLayoutParams(input,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                ConstraintLayout.LayoutParams.WRAP_CONTENT,
                0.5f
        );

        // Set the styles
        setLabelStyle(label);
        setInputStyle(input);
        setRoundedEdges(input, OLIVE);

        // Attach the text change listener to the input box
        input.addTextChangedListener(tch);
    }


    // Function to set the layout params of the children views
    void setChildrenLayoutParams(View v, int w, int h, float vbias) {
        // Create layout params
        ConstraintLayout.LayoutParams lp = new ConstraintLayout.LayoutParams(
                w, h
        );
        lp.startToStart = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.endToEnd  = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.bottomToBottom  = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.topToTop  = ConstraintLayout.LayoutParams.PARENT_ID;
        lp.verticalBias = vbias;

        // Set layout params
        v.setLayoutParams(lp);

        // Add to root view
        addView(v);
    }

    // Function to round the edges of a view
    void setRoundedEdges(View v, int color) {
        GradientDrawable rounded = new GradientDrawable();
        rounded.setShape(GradientDrawable.RECTANGLE);
        rounded.setCornerRadius(50f);
        rounded.setColor(color);
        v.setBackground(rounded);
    }

    // Set the style of the TextView
    void setLabelStyle(TextView tv) {
        tv.setPadding(200,50,200,50);
        tv.setText("Password strength");
        tv.setBackgroundColor(BROWN);
        tv.setTextSize(20);
        tv.setTypeface(Typeface.SERIF, Typeface.BOLD);
    }

    // Set the style of the EditText
    void setInputStyle(EditText et) {
        et.setBackgroundColor(BROWN);
        et.setPadding(165,20,165,20);
        et.setHint("Enter password");
        et.setTextSize(20);
    }

    // Set the label to say STRONG, and have green background
    void setLabelStrong() {
        label.setText("STRONG");
        label.setBackgroundColor(GREEN);
    }

    // Set the label to say WEAK, and have red background
    void setLabelWeak() {
        label.setText("WEAK");
        label.setBackgroundColor(RED);
    }

    // Reset the label to default style
    void resetLabel() {
        setLabelStyle(label);
    }
}
