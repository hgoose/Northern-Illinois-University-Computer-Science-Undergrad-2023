/**********************************************************
* *
* CSCI 470/502 Assignment 2 summer 2025 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 06/27/2025 *
* *
* Purpose: InvoiceTest class to test functionality of the Invoice class*
* *
**********************************************************/

import java.text.DecimalFormat;

/**********************************************************
* *
* CSCI 470/502 Assignment 2 summer 25 *
* *
* Class Name: InvoiceTest *
* *
* Developer(s): Nate Warner *
* *
* Purpose: Create 5 instances of the Invoice class to test functionality,
*          print data using get methods.
* *
**********************************************************/
public class InvoiceTest {
    /***************************************************************************
    * *
    * main used to create instances of Invoice class
    * *
    ****************************************************************************/
    public static void main(String[] args) {

        // Create 5 instances of the Invoice class with random data
        Invoice invoice1 = new Invoice(
                "P1234", 
                "Hammer", 
                15,
                25.50
        );

        Invoice invoice2 = new Invoice(
                "P5678", 
                "Screwdriver", 
                20, 
                12.75
        );

        Invoice invoice3 = new Invoice(
                "P9876", 
                "Wrench", 
                10, 
                18.30
        );

        Invoice invoice4 = new Invoice(
                "P3456", 
                "Drill", 
                5, 
                99.99
        );

        Invoice invoice5 = new Invoice(
                "P7890", 
                "Tape Measure", 
                25, 
                7.50
        );

        // For each invoice instance, output data
        Invoice[] invoices = {invoice1, invoice2, invoice3, invoice4, invoice5};
        for (int i=1; i<=5; ++i) {
            // Format price per item with the DecimalFormat class
            DecimalFormat Format = new DecimalFormat("$##,###,##0.00");

            // Print data for each invoice
            System.out.println("Invoice #" + i + '\n');
            System.out.println("        " + "Part No.: " + invoices[i-1].getPartNumber() + '\n');
            System.out.println("      " + "Item Desc.: " + invoices[i-1].getPartDesc() + '\n');
            System.out.println("        " + "Quantity.: " + invoices[i-1].getQty() + '\n');
            System.out.println("      " + "Item Price.: " + invoices[i-1].getPpi() + '\n');
            System.out.println("Invoice Subtotal:" + "      " + Format.format(invoices[i-1].getInvoiceAmount()) + '\n');
        }
    }
}
