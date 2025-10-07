/************************************************************************
 * *
 * CSCI 322/522 Assignment 3 fall 25 *
 * *
 * App Name: Addition App *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 10/06/2025 *
 * *
 * Purpose: Create a simple app to add two positive integers *
 * *
 ************************************************************************/
package edu.niu.z2004109.additionapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Button;
import android.view.View;
import android.text.TextWatcher;
import android.text.Editable;
import java.lang.CharSequence;

public class MainActivity extends AppCompatActivity {

    AdditionCalculator calc;

    TextView result;
    EditText firstNum;
    EditText secondNum;
    Button calculateButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Attach views to variables
        result = findViewById(R.id.mainLabel);
        firstNum = findViewById(R.id.firstNumber);
        secondNum = findViewById(R.id.secondNumber);
        calculateButton = findViewById(R.id.calculateButton);

        // Set onClick for calculate button
        calculateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    // Create AdditionCalculator instance
                    calc = new AdditionCalculator(
                            // Parse numbers in EditTexts to ints
                            Integer.parseInt(firstNum.getText().toString()),
                            Integer.parseInt(secondNum.getText().toString())
                    );
                    // Calculate result
                    int res = calc.calculate();
                    // Put result in TextView label
                    result.setText(Integer.toString(res));
                } catch (Exception e) {}
            }
        });
    }
}