/**********************************************************
* *
* CSCI 470/502 Assignment 6 summer 2025 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 08/1/2025 *
* *
* Purpose: gui-based Java application with which a travel agent could
            present options for travel destinations to a client who wants to redeem his or her accumulated frequent flyer
            miles
* *
**********************************************************/

import java.util.Scanner;
import java.util.ArrayList;
import java.io.IOException;
import java.io.File;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Comparator;

/**********************************************************
* *
* CSCI 470/502 Assignment 6 summer 25 *
* *
* Class Name: MileRedeemer
* *
* Developer(s): Nate Warner
* *
* Purpose: Write a class to encapsulate the logic for redeeming mileage
* *
**********************************************************/
public class MileRedeemer {
    // Data Members
    public Destination[] dests;
    private int remaining_miles;

    /***************************************************************************
    * *
    * Read an input file and create an array of destination objects sorted descending by normal ticket price *
    * *
    ****************************************************************************/
    public void readDestinations(Scanner fileScanner) throws IOException {
        // Create vector to store destination objects
        ArrayList<Destination> destinationList = new ArrayList<Destination>();

        while (fileScanner.hasNextLine()) {
            // Create new destination object
            Destination newDest = new Destination();

            // Get next line from file
            String data = fileScanner.nextLine();
            // Create string array of the fields
            String[] fields = data.split("[;-]");

            // Fill in data
            newDest.setDestCity(fields[0]);
            newDest.setNormTicketPrice(Integer.parseInt(fields[1]));
            newDest.setSuperTicketPrice(Integer.parseInt(fields[2]));
            newDest.setUpgradePrice(Integer.parseInt(fields[3]));
            newDest.setOsStart(Integer.parseInt(fields[4]));
            newDest.setOsEnd(Integer.parseInt(fields[5]));

            // Add to destination object to vector
            destinationList.add(newDest);

            // Convert vector to array and store in dests data member
            dests = (Destination[]) destinationList.toArray(new Destination[destinationList.size()]);

            // Sort descending by normal ticket price
            Arrays.sort(dests, Comparator.comparingInt(Destination::getNormTicketPrice).reversed());
        }
    }

    /***************************************************************************
    * *
    * Return an array of city names sorted ascending *
    * *
    ****************************************************************************/
    public String[] getCityNames() {
        // Create string array to hold city names
        String[] city_names = new String[dests.length];

        // Loop through destination objects
        for (int i=0; i<dests.length; ++i) {
            // Add city name to array
            city_names[i] = dests[i].getDestCity();
        }

        // Sort and return
        Arrays.sort(city_names);

        return city_names;
    }

    /***************************************************************************
    * *
    * Function to redeem accumulated frequent flier miles, find out which trips 
    * the user can take and if they can be upgraded to first class*
    * *
    ****************************************************************************/
    public String[] redeemMiles(int miles, int month) {
        // Parallel vectors
        ArrayList<String> trips = new ArrayList<String>();
        ArrayList<String> cities = new ArrayList<String>();
        ArrayList<Boolean> upgraded = new ArrayList<Boolean>();
        ArrayList<Integer> upgrade_price = new ArrayList<Integer>();

        // Loop through each destination object
        for (int i=0; i<dests.length; ++i) {
            // Check if super saver is available
            if (month >= dests[i].getOsStart() && month <= dests[i].getOsEnd()) {
                // Get the price
                int price = dests[i].getSuperTicketPrice();
                // If the user can afford the price
                if (miles >= price) {
                    // Add information to arrays
                    cities.add(dests[i].getDestCity());
                    upgraded.add(false);
                    upgrade_price.add(dests[i].getUpgradePrice());

                    // Update miles
                    miles-=price;
                }
            // Super saver is not available
            } else {
                // Get the price
                int price = dests[i].getNormTicketPrice();
                // If the user can afford the price
                if (miles >= price) {
                    // Add information to arrays
                    cities.add(dests[i].getDestCity());
                    upgraded.add(false);
                    upgrade_price.add(dests[i].getUpgradePrice());

                    // Update miles
                    miles-=price;
                }
            }
        }

        // Loop through available trips and see if an upgrade is available
        for (int i=0; i<cities.size(); ++i) {
            // If the user can afford the upgrade price
            if (miles >= upgrade_price.get(i)) {
                // Set upgraded to true
                upgraded.set(i, true); 

                // Update miles
                miles-=upgrade_price.get(i);
            }
            // Build the trip info string
            String trip = cities.get(i) + " in " + (upgraded.get(i) ? "First Class" : "Economy Class");
            // Add to return array
            trips.add(trip);
        }

        // Set remaining miles data member
        remaining_miles = miles;

        // Return vector to array conversion
        return trips.toArray(new String[trips.size()]);
    }

    /***************************************************************************
    * *
    * Return the remaining miles data member *
    * *
    ****************************************************************************/
    public int getRemainingMiles() {
        return remaining_miles;
    }
}
