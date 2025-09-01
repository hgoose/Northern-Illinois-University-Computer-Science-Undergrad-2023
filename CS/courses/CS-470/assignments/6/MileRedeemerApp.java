/**********************************************************
* *
* CSCI 470/502 Assignment 6 summer 2025 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 08/1/2025 *
* *
* Purpose: gui-based Java application with which a travel agent could
            miles
            present options for travel destinations to a client who wants to redeem his or her accumulated frequent flyer
* *
**********************************************************/

import java.util.Scanner;
import java.io.File;
import java.io.IOException;

/**********************************************************
* *
* CSCI 470/502 Assignment 6 summer 25 *
* *
* Class Name: MileRedeemerApp
* *
* Developer(s): Nate Warner
* *
* Purpose: Main function of the app
* *
**********************************************************/

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.stage.FileChooser;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MileRedeemerApp extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("MileRedeemer.fxml"));
        Scene scene = new Scene(root); // attach scene graph to scene
        stage.setTitle("Mile Redeemer"); //displayed in window's title
        stage.setScene(scene); // attach scene to stage
        stage.show(); // display the stage
    }
}
