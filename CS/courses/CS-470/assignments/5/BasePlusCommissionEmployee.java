/**********************************************************
* *
* CSCI 470/502 Assignment 5 summer 2025 *
* *
* Developer(s): Nate Warner *
* *
* Due Date: 07/25/2025 *
* *
* Purpose: Modify the payroll system code *
* *
**********************************************************/

// BasePlusCommissionEmployee.java
// BasePlusCommissionEmployee class extends CommissionEmployee.

/**********************************************************
* *
* CSCI 470/502 Assignment 5 summer 25 *
* *
* Class Name: BasePlusCommissionEmployee
* *
* Developer(s): Nate Warner
*
* Purpose: Represents an employee that makes commission plus a base
* *
**********************************************************/
public class BasePlusCommissionEmployee extends CommissionEmployee {

   private double baseSalary; // base salary per week

   // constructor
   public BasePlusCommissionEmployee(String firstName, String lastName,
      String socialSecurityNumber, Date birthDate, double grossSales,
      double commissionRate, double baseSalary) {
   
      super(firstName, lastName, socialSecurityNumber, birthDate,
         grossSales, commissionRate);

      if (baseSalary < 0.0) // validate baseSalary                  
         throw new IllegalArgumentException("Base salary must be >= 0.0");
            
      this.baseSalary = baseSalary;                
   }

   // set base salary
   public void setBaseSalary(double baseSalary) {
   
      if (baseSalary < 0.0) // validate baseSalary                  
         throw new IllegalArgumentException("Base salary must be >= 0.0");
            
      this.baseSalary = baseSalary;                
   } 

   // return base salary
   public double getBaseSalary() {
   
      return baseSalary;
   }

   // calculate earnings; override method earnings in CommissionEmployee
   @Override                                                            
   public double earnings() {                                            
                                           
      return getBaseSalary() + super.earnings();                        
   } 

   // return String representation of BasePlusCommissionEmployee object
   @Override                                                           
   public String toString() {                                           
                                             
      return String.format("%s %s; %s: $%,.2f",                       
         "base-salaried", super.toString(),                            
         "base salary", getBaseSalary());                             
   } 
}
