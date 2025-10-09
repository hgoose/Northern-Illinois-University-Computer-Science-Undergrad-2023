/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Password Validator *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/13/2025 *
 * *
 * Purpose: Controller class of the application
 * *
 ************************************************************************/
package edu.niu.z2004109.passwordvalidator;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ViewGroup;
import android.text.TextWatcher;
import android.text.Editable;
import java.lang.CharSequence;

public class MainActivity extends AppCompatActivity {
    // Members
    PasswordValidator validator;
    PasswordValidatorView view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Create the listener
        TextChangeHandler tch = new TextChangeHandler();

        // Create the model instance
        validator = new PasswordValidator();

        // Create the view
        view = new PasswordValidatorView(this,
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT,
                tch
        );

        // Set root view to view class instance
        setContentView(view);
    }

    // Listens for text change, updates label text and background color
    private class TextChangeHandler implements TextWatcher {
        // Stubs
        public void beforeTextChanged(CharSequence s, int start,int count, int after) {}
        public void onTextChanged(CharSequence s, int start, int before, int after) {}

        // The one we care about
        public void afterTextChanged(Editable e) {
            // Set the password in the model instance
            validator.setPassword(e.toString());

            // Check if it's strong or weak
            int valid = validator.validate();

            // Update the label
            if (valid == 1) {
                view.setLabelStrong();
            } else if (valid == 0) {
                view.setLabelWeak();
            } else {
                view.resetLabel();
            }
        }
    }
}