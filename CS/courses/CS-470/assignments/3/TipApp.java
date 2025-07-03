/**********************************************************
* *
* CSCI 470/502 Assignment 3 summer 2025 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 07/05/2025 *
* *
* Purpose: Java console app to calculate tips *
* *
**********************************************************/

import java.util.Scanner;

/**********************************************************
* *
* CSCI 470/502 Assignment 3 summer 25 *
* *
* Class Name: TipApp
* *
* Developer(s): Nate Warner *
* *
* Purpose: This class encapsulates the user interface of the app.
* *
**********************************************************/
public class TipApp {
    // Data Members: TipCalculator object and Scanner for keyboard input
    static TipCalculator calculator = new TipCalculator();
    static Scanner sc = new Scanner(System.in);

    // Entry
    public static void main(String[] args) {
        System.out.println("\n*** Tip Calculator ***\n");

        boolean cont = true;
        while (cont) {
            cont = false;

            // Call calculateTips to get the user input and store into the calculator object
            calculateTips();

            // Output gathered data
            System.out.println("\n*** Your Bill ***\n");
            System.out.printf("Bill Amount: $%.2f\n", calculator.getBillAmount());
            System.out.println("Tip Percentage: " + calculator.getTipPercent() + "%");
            System.out.println("Party Size: " + calculator.getPartySize() + '\n');
            System.out.printf("Total Bill (with Tip): $%.2f\n", calculator.getTotalBill());
            System.out.printf("Share for Each Individual: $%.2f\n\n", calculator.getIndividualShare());

            // Ask for another bill
            System.out.print("Another bill? (y/n): ");

            // Retrieve answer
            String answer = sc.nextLine();

            // If answer is yes, continue loop
            if (answer.equalsIgnoreCase("y")) {
                cont = true;
                System.out.println("");
            } 
        }

        // Close scanner
        sc.close();
    }

    /***************************************************************************
    * *
    * Gather user input and store in static calculator object *
    * *
    ****************************************************************************/
    public static void calculateTips() {
        // Get the bill amount
        System.out.print("Enter bill amount: ");
        String tmp_amount = sc.nextLine();

        // Verify that the bill amount is a double
        while (!tmp_amount.matches("\\d+.?\\d*")) {
            System.out.print("Enter bill amount: ");
            tmp_amount = sc.nextLine();
        }

        // Set the bill amount
        calculator.setBillAmount(Double.parseDouble(tmp_amount));

        // Get the tip percentage
        System.out.print("Enter tip percentage: ");
        String tmp_prcnt = sc.nextLine();

        // Verify that the tip percent is a int
        // The regex match handles the case of negative input (the pattern does not allow for a minus sign)
        while (!tmp_prcnt.matches("\\d+") || Integer.parseInt(tmp_prcnt) > 100) {
            System.out.print("Enter tip percentage: ");
            tmp_prcnt = sc.nextLine();
        }

        // Set the tip percentage
        calculator.setTipPercent(Integer.parseInt(tmp_prcnt));

        // Get the party size
        System.out.print("Enter party size: ");
        String tmp_size = sc.nextLine();

        // Verify that the party size is an int
        while (!tmp_size.matches("\\d+")) {
           System.out.print("Enter party size: ");
           tmp_size = sc.nextLine();
        }

        // Set the party size
        calculator.setPartySize(Integer.parseInt(tmp_size));
    }
}
