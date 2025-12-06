/************************************************************************
 * *
 * CSCI 322/522 Assignment 7 fall 25 *
 * *
 * App Name: Tap it *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 12/5/2025 *
 * *
 * Purpose: Controller + view for application
 * *
 ************************************************************************/

package edu.niu.android.tapit;

import android.content.Context;
import android.graphics.Typeface;
import android.os.Bundle;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.view.GestureDetector;
import android.graphics.Color;
import android.view.Gravity;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;

public class MainActivity extends AppCompatActivity implements GestureDetector.OnGestureListener, GestureDetector.OnDoubleTapListener {
    RelativeLayout layout;
    GestureDetector detector;
    TextView colored;
    TextView counter;

    // Colors
    int blue;
    int red;
    int lavendar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Set colors
        blue = Color.parseColor("#7F83FA");
        red = Color.parseColor("#A3394F");
        lavendar = Color.parseColor("#A578CC");

        // Bulid the UI
        buildUI();

        // Set the root view
        setContentView(layout);
    }

    // Function to build the view
    private void buildUI() {

        // Create root layout, set layout params
        layout = new RelativeLayout(this);
        ViewGroup.LayoutParams vlp = new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
        );
        layout.setLayoutParams(vlp);

        // Create two textviews
        colored = new TextView(this);
        colored.setId(View.generateViewId());
        counter = new TextView(this);

        // Set the layout params for the colored box, size and position
        RelativeLayout.LayoutParams colored_params = new RelativeLayout.LayoutParams(
                400, 200
        );
        // Positioning
        colored_params.addRule(RelativeLayout.CENTER_VERTICAL);
        colored_params.addRule(RelativeLayout.CENTER_HORIZONTAL);
        // Margin
        colored_params.bottomMargin = 50;
        // Set layout params for colored TextView
        colored.setLayoutParams(colored_params);

        // Style colored TextView
        styleTextView(colored, blue, Gravity.CENTER, "Single tap me");

        // Set the layout params for the counter box, size and position
        RelativeLayout.LayoutParams counter_params = new RelativeLayout.LayoutParams(
                400, 200
        );
        // Positioning
        counter_params.addRule(RelativeLayout.BELOW, colored.getId());
        counter_params.addRule(RelativeLayout.CENTER_HORIZONTAL);
        // Set layout params for the counter TextView
        counter.setLayoutParams(counter_params);
        // Style counter TextView
        styleTextView(counter, lavendar, Gravity.CENTER, "0");

        // Add TextViews to root layout
        layout.addView(colored);
        layout.addView(counter);

        // Create GestureDetector object
        detector = new GestureDetector(this, this);
        detector.setOnDoubleTapListener(this);

        // Route touch events on colored TextView to GestureDetector object
        colored.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                detector.onTouchEvent(event);
                return true;
            }
        });
    }

    // Function to style a TextView
    private void styleTextView(TextView tv, int color, int gravity, String message) {
        tv.setBackgroundColor(color);
        tv.setGravity(gravity);
        tv.setText(message);
        tv.setTypeface(null, Typeface.BOLD);
    }

    // Updates the properties of a textview. Background color and text
    private void updateTextView(TextView tv, int color, String message) {
        tv.setBackgroundColor(color);
        tv.setText(message);
    }

    // Change to red after single tap
    private void changeToDoubleTap() {
        updateTextView(colored, red, "Double tap me");
    }

    // Change to blue after double tap
    private void changeToSingleTap() {
        updateTextView(colored, blue, "Single tap me");
    }

    // Increment the count inside the counter after even single / double tap
    private void incCount() {
        // Get current count
        String str_count = counter.getText().toString();
        // This is perfectly safe
        int count = Integer.parseInt(str_count);
        // Update count
        counter.setText("" + (count + 1));
    }

    // When a single tap is confirmed
    @Override
    public boolean onSingleTapConfirmed(@NonNull MotionEvent e) {
        // Increment the tap count
        incCount();
        // Change to red
        changeToDoubleTap();
        // Event handled
        return true;
    }

    // When a double tap is confirmed
    @Override
    public boolean onDoubleTap(@NonNull MotionEvent e) {
        // Increment the tap count
        incCount();
        // Change to blue
        changeToSingleTap();
        // Event handled
        return true;
    }

    @Override
    public boolean onDoubleTapEvent(@NonNull MotionEvent e) {
        return false;
    }

    @Override
    public boolean onDown(@NonNull MotionEvent e) {
        return false;
    }

    @Override
    public boolean onFling(@Nullable MotionEvent e1, @NonNull MotionEvent e2, float velocityX, float velocityY) {
        return false;
    }

    @Override
    public void onLongPress(@NonNull MotionEvent e) {

    }

    @Override
    public boolean onScroll(@Nullable MotionEvent e1, @NonNull MotionEvent e2, float distanceX, float distanceY) {
        return false;
    }

    @Override
    public void onShowPress(@NonNull MotionEvent e) {

    }

    @Override
    public boolean onSingleTapUp(@NonNull MotionEvent e) {
        return false;
    }
}