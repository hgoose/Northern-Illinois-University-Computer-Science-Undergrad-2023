/**********************************************************
* *
* CSCI 470/502 Assignment 4 summer 2025 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 07/18/2025 *
* *
* Purpose: Console-based Java application with which a travel agent could
            present options for travel destinations to a client who wants to redeem his or her accumulated frequent flyer
            miles
* *
**********************************************************/

import java.util.Scanner;
import java.io.File;
import java.io.IOException;

/**********************************************************
* *
* CSCI 470/502 Assignment 4 summer 25 *
* *
* Class Name: MileRedeemerApp
* *
* Developer(s): Nate Warner
* *
* Purpose: Main function of the app
* *
**********************************************************/
public class MileRedeemerApp {
    public static void main(String[] args) throws IOException {
        // Scanners for file name and if the user wants to continue
        Scanner input = new Scanner(System.in);
        Scanner input_continue = new Scanner(System.in);

        // Get the input file from the user
        System.out.print("Enter input file: ");
        String file_name = input.nextLine();

        // Create Scanner to read from requested file
        File file = new File(file_name);
        Scanner reader = new Scanner(file);

        // Create MileRedeemer object
        MileRedeemer redeemer = new MileRedeemer();

        // Call readDestinations
        redeemer.readDestinations(reader);

        // Get the list of city names
        String[] city_names = redeemer.getCityNames();

        System.out.println("\n----------------------------------------------------------------\n\tWELCOME TO THE JAVA AIRLINES MILES REDEEMER APP\n----------------------------------------------------------------\n");
        System.out.println("List of destination cities your client can travel to:\n");

        // Output available cities
        for (int i=0; i<city_names.length; ++i) {
            System.out.println(city_names[i]);
        }

        System.out.println("\n----------------------------------------------------------------\n");

        boolean cont = true;
        while (cont) {
            cont = false;

            // Get miles from user
            System.out.print("Please enter your client's accumulated Frequent Flyer Miles: "); 
            int miles = input.nextInt();

            // Get month from user
            System.out.print("\nPlease enter your client's month of departure (1-12): ");
            int month = input.nextInt();

            System.out.println();

            // Get list of trips the user can take
            String[] trips = redeemer.redeemMiles(miles, month);

            // Check if list of trips is empty
            if (trips.length != 0) {
                // If not empty, output each trip
                for (int i=0; i<trips.length; ++i) {
                    System.out.println("* A trip to " + trips[i]);
                }
            } else System.out.println("*** Your client has not accumulated enough Frequent Flyer Miles ***");

            // Output remaining miles
            System.out.println("\nYour client's remaining Frequent Flyer Miles: " + redeemer.getRemainingMiles());

            // Ask the user if they want to continue
            System.out.println("\n----------------------------------------------------------------\n");
            System.out.print("Do you want to continue (y/n)? ");

            String ans = input_continue.nextLine();
            if (ans.equalsIgnoreCase("y")) {
                cont = true;
            } 
            System.out.println("\n----------------------------------------------------------------\n");
        }

        input.close();
        input_continue.close();
        System.out.println("\n-------------------------------------------------------------------------\n\tTHANK YOU FOR USING THE JAVA AIRLINES MILES REDEEMER APP\n-------------------------------------------------------------------------");
    }
}
