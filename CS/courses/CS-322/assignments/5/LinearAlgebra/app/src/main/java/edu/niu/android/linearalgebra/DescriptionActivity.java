/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Linear Algebra
 * *
 * Class Name: DescriptionActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/03/2025 *
 * *
 * Purpose: Second activity that shows image and description
 * *
 ************************************************************************/
package edu.niu.android.linearalgebra;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import androidx.appcompat.app.AppCompatActivity;
import android.widget.ImageView;
import android.widget.TextView;

public class DescriptionActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_description);

        // Get the views
        ImageView img = findViewById(R.id.detailImage);
        TextView tv  = findViewById(R.id.detailText);
        Button back = findViewById(R.id.backButton);

        // Get the image id and description from Intent
        Intent i = getIntent();
        int imageId = i.getIntExtra("imageId", 0);
        String desc = i.getStringExtra("description");

        // Get image name
        String png = "use" + (imageId + 1);
        int pngId = getResources().getIdentifier(png, "drawable", getPackageName());

        // Set image on ImageView
        img.setImageResource(pngId);

        // Set the labels text
        tv.setText(desc);

        // Create back button
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DescriptionActivity.this.finish();
            }
        });
    }
}
