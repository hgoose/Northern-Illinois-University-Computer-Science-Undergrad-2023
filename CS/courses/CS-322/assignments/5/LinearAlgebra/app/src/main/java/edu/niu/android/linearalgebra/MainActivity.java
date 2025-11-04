/************************************************************************
 * *
 * CSCI 322/522 Assignment 5 fall 25 *
 * *
 * App Name: Linear Algebra *
 * *
 * Class Name: MainActivity.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/03/2025 *
 * *
 * Purpose: Main Activity
 * *
 ************************************************************************/
package edu.niu.android.linearalgebra;

// Includes
import android.os.Bundle;
import android.graphics.Point;
import androidx.appcompat.app.AppCompatActivity;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.ImageButton;
import android.view.View;
import android.view.Gravity;
import android.graphics.Typeface;
import android.content.Intent;

public class MainActivity extends AppCompatActivity {

    private GridLayout grid;
    private static final int rows = 4;
    private static final int cols = 3;

    // Model
    public ConceptDescription description;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Build the view
        updateView();
        setContentView(grid);
    }

    @Override
    protected void onResume() {
        super.onResume();
        // Rebuild the view
        updateView();
    }

    private void updateView() {
        // Get the dimensions
        Point size = new Point();
        getWindowManager().getDefaultDisplay().getSize(size);

        // Create the root layout
        grid = new GridLayout(this);
        ViewGroup.MarginLayoutParams mlp = new ViewGroup.MarginLayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT
        );
        // Push the layout down
        mlp.setMargins(0,size.y/4,0,0);
        grid.setLayoutParams(mlp);

        // Set rows and columns
        grid.setRowCount(rows);
        grid.setColumnCount(cols);

        // Create the label, and style
        TextView label = new TextView(this);
        label.setText("Select concept");
        setLabelStyle(label);
        setGridChildLayoutParams(label,0,0, cols, GridLayout.LayoutParams.MATCH_PARENT, GridLayout.LayoutParams.MATCH_PARENT);

        // On click handler
        ButtonHandler bh = new ButtonHandler();

        // Create each ImageButton
        for (int i=1; i<rows; ++i) {
            for (int j=0; j<cols; ++j) {
                // Get the png name
                String png = "use" + (((i-1)*cols) + (j+1));
                System.out.println("PNG:" + png);
                int pngId = getResources().getIdentifier(png, "drawable", getPackageName());

                // Create and style button
                ImageButton button = new ImageButton(this);
                button.setImageResource(pngId);
                button.setScaleType(ImageView.ScaleType.FIT_XY);
                button.setBackground(null);
                button.setPadding(0,0,0,0);
                button.setAdjustViewBounds(true);
                button.setId((i-1)*cols + j);

                // Set the listener
                button.setOnClickListener(bh);

                // Add to grid
                setGridChildLayoutParams(button, i,j, 1, size.x/(rows-1), 300);
            }
        }
    }

    private void setGridChildLayoutParams(View v, int row, int col, int colspan, int width, int height) {
        // Set row, column position
        GridLayout.Spec r = GridLayout.spec(row);
        GridLayout.Spec c = GridLayout.spec(col, colspan);

        // Create layout params, set width and height
        GridLayout.LayoutParams lp = new GridLayout.LayoutParams(r, c);
        lp.width = width;
        lp.height = height;

        // Set the LayoutParams for child view
        v.setLayoutParams(lp);
        // Add child to grid
        grid.addView(v);
    }

    // Sets style of label
    private void setLabelStyle(TextView label) {
        label.setTextSize(20);
        label.setGravity(Gravity.CENTER);
        label.setTypeface(null, Typeface.BOLD);
    }

    private class ButtonHandler implements View.OnClickListener {
        public void onClick(View v) {
            // Create intent, send description and imageId
            Intent descIntent = new Intent(MainActivity.this, DescriptionActivity.class);
            String desc = ConceptDescription.descriptions[v.getId()];
            descIntent.putExtra("description", desc);
            descIntent.putExtra("imageId", v.getId());

            // Start new activity
            MainActivity.this.startActivity(descIntent);
        }
    }

}