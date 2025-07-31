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

public class MileRedeemerController implements Initializable {

    public MileRedeemer redeemer = new MileRedeemer();
    public static String[] months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    public int month = 0;
    public int miles = 0;

    @FXML
    private Button button_FileChooser;

    @FXML 
    private ListView<String> destinationListView;

    @FXML
    private TextField normal_miles;

    @FXML
    private TextField supersaver_miles;

    @FXML
    private TextField upgrade_cost;

    @FXML
    private TextField supersaver_dates;

    @FXML
    private TextField miles_remain;

    @FXML
    private ChoiceBox<String> month_select;

    @FXML
    private TextField input_miles;

    @FXML
    private ListView<String> tripsListView;

    @FXML
    void ChooseFile(ActionEvent event) throws IOException {
        FileChooser chooser = new FileChooser();
        chooser.setTitle("Open Destination File");

        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();

        File selectedFile = chooser.showOpenDialog(stage);
        Scanner reader = new Scanner(selectedFile);

        if (selectedFile != null) {
            redeemer.readDestinations(reader);

            ObservableList<String> items = FXCollections.observableArrayList();
            for (Destination dest : redeemer.dests) {
                items.add(dest.getDestCity());
            }

            destinationListView.setItems(items);
        }
    }

    @FXML
    void RedeemMiles(ActionEvent event) {
        String month_str = month_select.getValue();
        String miles_str = input_miles.getText();

        for (int i=0; i<months.length; ++i) {
            if (months[i].equalsIgnoreCase(month_str)) {
                month = i;
            }
        }

        try {
            miles = Integer.parseInt(miles_str.trim());
        } catch (NumberFormatException nfe) {
            System.err.println("Invalid input for miles");
            return;
        }

        String[] trips = redeemer.redeemMiles(miles, month);
        miles_remain.setText(String.valueOf(redeemer.getRemainingMiles()));

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

    private void onDestinationSelected(ObservableValue<? extends String> obs,
            String oldCity, String newCity)
    {
        if (newCity == null) return;

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

