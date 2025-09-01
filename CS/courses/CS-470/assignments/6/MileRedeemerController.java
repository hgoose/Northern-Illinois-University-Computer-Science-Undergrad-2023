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

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.scene.Node;
import java.io.File;
import java.util.Scanner;
import java.io.IOException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.fxml.Initializable;
import javafx.beans.value.ObservableValue;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.scene.control.ChoiceBox;

/**********************************************************
* *
* CSCI 470/502 Assignment 6 summer 25 *
* *
* Class Name: MileRedeemerController
* *
* Developer(s): Nate Warner
* *
* Purpose: Controller for Mile Redeemer App
* *
**********************************************************/
public class MileRedeemerController implements Initializable {

    private MileRedeemer redeemer = new MileRedeemer();
    private static String[] months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    private int month = 0;
    private int miles = 0;

    // fx:id widgets
    @FXML private Button button_FileChooser;
    @FXML private ListView<String> destinationListView;
    @FXML private TextField normal_miles;
    @FXML private TextField supersaver_miles;
    @FXML private TextField upgrade_cost;
    @FXML private TextField supersaver_dates;
    @FXML private TextField miles_remain;
    @FXML private ChoiceBox<String> month_select;
    @FXML private TextField input_miles;
    @FXML private ListView<String> tripsListView;

    // On action for input button, used to select text file containing available destinations
    @FXML
    void ChooseFile(ActionEvent event) throws IOException {
        // Create chooser
        FileChooser chooser = new FileChooser();
        // Set title
        chooser.setTitle("Open Destination File");

        // Create stage
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();

        // Create file object from stage
        File selectedFile = chooser.showOpenDialog(stage);
        // Create scanner from file
        Scanner reader = new Scanner(selectedFile);

        // If file not null
        if (selectedFile != null) {
            // Pass file to readDestinations on redeemer object
            redeemer.readDestinations(reader);

            // Collection of the destination objects for a ListView
            ObservableList<String> items = FXCollections.observableArrayList();
            for (Destination dest : redeemer.dests) {
                // Add to list view
                items.add(dest.getDestCity());
            }

            // Add to list view
            destinationListView.setItems(items);
        }
    }

    // On action for redeem miles button
    @FXML
    void RedeemMiles(ActionEvent event) {
        String month_str = month_select.getValue();
        String miles_str = input_miles.getText();

        // Find the month number
        for (int i=0; i<months.length; ++i) {
            if (months[i].equalsIgnoreCase(month_str)) {
                month = i;
            }
        }

        // Try to convert miles to an integer
        try {
            miles = Integer.parseInt(miles_str.trim());
        } catch (NumberFormatException nfe) {
            System.err.println("Invalid input for miles");
            return;
        }

        // Call redeemMiles to get list of trip descriptions
        String[] trips = redeemer.redeemMiles(miles, month);

        // Set text of miles_remain widget (text field)
        miles_remain.setText(String.valueOf(redeemer.getRemainingMiles()));

        // List view of trips
        ObservableList<String> items = FXCollections.observableArrayList();
        for (String trip : trips) {
            items.add(trip);
        }
        tripsListView.setItems(items);
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        destinationListView.getSelectionModel()
            .selectedItemProperty()
            .addListener(this::onDestinationSelected);
        
        month_select.getItems().addAll(months);
    }

    /// On action for when a destination is selected
    private void onDestinationSelected(ObservableValue<? extends String> obs,
            String oldCity, String newCity)
    {
        if (newCity == null) return;

        // Display information
        for (Destination d : redeemer.dests) {
            if (d.getDestCity().equals(newCity)) {
                normal_miles.setText(String.valueOf(d.getNormTicketPrice()));
                supersaver_miles.setText(String.valueOf(d.getSuperTicketPrice()));
                upgrade_cost.setText(String.valueOf(d.getUpgradePrice()));
                supersaver_dates.setText(months[d.getOsStart()] + " – " + months[d.getOsEnd()]);
                break;
            }
        }
    }
}

