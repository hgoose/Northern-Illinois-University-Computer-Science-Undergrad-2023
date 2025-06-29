/**********************************************************
* *
* CSCI 470/502 Assignment 2 summer 25 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 06/27/20205 *
* *
* Purpose: Class that represents an invoice that a hardware store might use.*
* *
**********************************************************/

/**********************************************************
* *
* CSCI 470/502 Assignment 2 summer 25
* *
* Class Name: Invoice *
* *
* Developer(s): Nate Warner *
* *
* Purpose: Represents an invoice that a hardware store might use *
* *
**********************************************************/
public class Invoice {
    // Data Members
    String part_number;
    String part_desc;
    int qty;
    double ppi;

    // Default constructor
    public Invoice() {
        part_number = "";
        part_desc = "";
        qty = 0;
        ppi = 0.0;
    }

    // Parameterized constructor
    public Invoice(String part_number, String part_desc, int qty, double ppi) {
        this.part_number = part_number;
        this.part_desc = part_desc;
        this.qty = (qty >= 0 ? qty : 0);
        this.ppi = (ppi >= 0 ? ppi : 0.0);
    }

    /***************************************************************************
    * *
    * getPartNumber returns the part number member *
    * *
    ****************************************************************************/
    public String getPartNumber() {
        return part_number;
    }

    /***************************************************************************
    * *
    * setPartNumber sets the part number member *
    * *
    ****************************************************************************/
    public void setPartNumber (String part_number) {
        this.part_number = part_number;
    }

    /***************************************************************************
    * *
    * getPartDesc returns the part description member *
    * *
    ****************************************************************************/
    public String getPartDesc() {
        return part_desc;
    }

    /***************************************************************************
    * *
    * setPartDesc sets the part desc member *
    * *
    ****************************************************************************/
    public void setPartDesc (String part_desc) {
        this.part_desc = part_desc;
    }

    /***************************************************************************
    * *
    * getQty returns the qty member *
    * *
    ****************************************************************************/
    public int getQty() {
       return qty; 
    }

    /***************************************************************************
    * *
    * setQty sets the quantity member
    * *
    ****************************************************************************/
    public void setQty (int qty) {
        this.qty = (qty >= 0 ? qty : 0);
    }

    /***************************************************************************
    * *
    * getPpi returns the price per item member *
    * *
    ****************************************************************************/
    public double getPpi() {
        return ppi;
    }

    /***************************************************************************
    * *
    * setPpi sets the price per item member
    * *
    ****************************************************************************/
    public void setPpi (double ppi) {
        this.ppi = (ppi >= 0.0 ? ppi : 0.0);
    }

    /***************************************************************************
    * *
    * getInvoiceAmount calculates and returns the invoice amount, which is 
    *                  quantity multiplet by the price per item (double).
    * *
    ****************************************************************************/
    public double getInvoiceAmount() {
        return qty * ppi;
    }
}
