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

/**********************************************************
* *
* CSCI 470/502 Assignment 6 summer 25 *
* *
* Class Name: Destination
* *
* Developer(s): Nate Warner
* *
* Purpose: encapsulates information such as the name of the destination city; normal miles required
           for a ticket; "super-saver" miles required to for a ticket during the "off season" months; additional miles for
           upgrading from economy to first class; start month of the "off season" and end month of the "off season".
* *
**********************************************************/
public class Destination {
    // Data Members
    private String dest_city;
    private int norm_ticket_price;
    private int super_ticket_price;
    private int upgrade_price;
    private int os_start;
    private int os_end;

    // Default constructor
    public Destination() {
        dest_city = "";
        norm_ticket_price = 0;
        super_ticket_price = 0;
        upgrade_price = 0;
        os_start = 0;
        os_end = 0;
    }

    // Parameterized constructor
    public Destination(String dest_city, int norm_ticket_price, int super_ticket_price,
                       int upgrade_price, int os_start, int os_end) {
        this.dest_city = dest_city;
        this.norm_ticket_price = norm_ticket_price;
        this.super_ticket_price = super_ticket_price;
        this.upgrade_price = upgrade_price;
        this.os_start = os_start;
        this.os_end = os_end;
    }

    /***************************************************************************
    * *
    * Returns the destination city member *
    * *
    ****************************************************************************/
    public String getDestCity() {
        return dest_city;
    }

    /***************************************************************************
    * *
    * Returns the normal ticket price member *
    * *
    ****************************************************************************/
    public int getNormTicketPrice() {
        return norm_ticket_price;
    }

    /***************************************************************************
    * *
    * Returns the super ticket price member *
    * *
    ****************************************************************************/
    public int getSuperTicketPrice() {
        return super_ticket_price;
    }

    /***************************************************************************
    * *
    * Returns the upgrade price member *
    * *
    ****************************************************************************/
    public int getUpgradePrice() {
        return upgrade_price;
    }

    /***************************************************************************
    * *
    * Returns the off-season start date member *
    * *
    ****************************************************************************/
    public int getOsStart() {
        return os_start;
    }

    /***************************************************************************
    * *
    * Returns the off-season end date member *
    * *
    ****************************************************************************/
    public int getOsEnd() {
        return os_end;
    }

    // Setters

    /***************************************************************************
    * *
    * Sets the destination city member *
    * *
    ****************************************************************************/
    public void setDestCity(String dest_city) {
        this.dest_city = dest_city;
    }

    /***************************************************************************
    * *
    * Sets the normal ticket price member *
    * *
    ****************************************************************************/
    public void setNormTicketPrice(int norm_ticket_price) {
        this.norm_ticket_price = norm_ticket_price;
    }

    /***************************************************************************
    * *
    * Sets the super ticket price member *
    * *
    ****************************************************************************/
    public void setSuperTicketPrice(int super_ticket_price) {
        this.super_ticket_price = super_ticket_price;
    }

    /***************************************************************************
    * *
    * Sets the upgrade price member *
    * *
    ****************************************************************************/
    public void setUpgradePrice(int upgrade_price) {
        this.upgrade_price = upgrade_price;
    }

    /***************************************************************************
    * *
    * Sets the off-season start date member *
    * *
    ****************************************************************************/
    public void setOsStart(int os_start) {
        this.os_start = os_start;
    }

    /***************************************************************************
    * *
    * Sets the off-season end date member *
    * *
    ****************************************************************************/
    public void setOsEnd(int os_end) {
        this.os_end = os_end;
    }
}
