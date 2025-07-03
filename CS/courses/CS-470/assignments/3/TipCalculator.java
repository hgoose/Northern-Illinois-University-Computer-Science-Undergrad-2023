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

/**********************************************************
* *
* CSCI 470/502 Assignment 3 summer 25 *
* *
* Class Name: TipCalculator
* *
* Developer(s): Nate Warner *
* *
* Purpose: Object to hold information about a party's bill
* *
**********************************************************/
public class TipCalculator {
    // Data members
    private double bill_amount;
    private int tip_prcnt;
    private int party_size;

    // Default constructor
    public TipCalculator() {
        bill_amount = 0.0;
        tip_prcnt = 20;
        party_size = 0;
    }

    // Parameterized constructor
    public TipCalculator(double bill_amount, int tip_prcnt, int party_size) {
        this.bill_amount = bill_amount;
        this.tip_prcnt = tip_prcnt;
        this.party_size = party_size;
    }

    /***************************************************************************
    * *
    * Return the bill amount member *
    * *
    ****************************************************************************/
    public double getBillAmount() {
        return bill_amount;
    }

    /***************************************************************************
    * *
    * Sets the bill amount member *
    * *
    ****************************************************************************/
    public void setBillAmount(double bill_amount) {
        this.bill_amount = bill_amount;
    }

    /***************************************************************************
    * *
    * Return the tip percent member *
    * *
    ****************************************************************************/
    public int getTipPercent() {
        return tip_prcnt;
    }

    /***************************************************************************
    * *
    * Sets the tip percent member *
    * *
    ****************************************************************************/
    public void setTipPercent(int tip_prcnt) {
        this.tip_prcnt = tip_prcnt;
    }

    /***************************************************************************
    * *
    * Returns the party size member *
    * *
    ****************************************************************************/
    public int getPartySize() {
        return party_size;
    }

    /***************************************************************************
    * *
    * Sets the party size member *
    * *
    ****************************************************************************/
    public void setPartySize(int party_size) {
        this.party_size = party_size;
    }

    /***************************************************************************
    * *
    * Calculate and return the total bill *
    * *
    ****************************************************************************/
    public double getTotalBill() {
        return bill_amount + (bill_amount * (tip_prcnt / 100.0));
    }

    /***************************************************************************
    * *
    * Calculate and return the individual share *
    * *
    ****************************************************************************/
    public double getIndividualShare() {
        return (party_size > 0 ? getTotalBill() / party_size : 0.0);
    }
}
