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


// Employee.java
// Employee abstract superclass.

/**********************************************************
* *
* CSCI 470/502 Assignment 5 summer 25 *
* *
* Class Name: CommissionEmployee
* *
* Developer(s): Nate Warner
*
* Purpose: Represents an employee 
* *
**********************************************************/
public abstract class Employee {

   private final String firstName;
   private final String lastName;
   private final String socialSecurityNumber;
   private Date birthDate;

   // constructor
   public Employee(String firstName, String lastName, String socialSecurityNumber, Date birthDate) {
   
      this.firstName = firstName;                                    
      this.lastName = lastName;                                    
      this.socialSecurityNumber = socialSecurityNumber;         
      this.birthDate = birthDate;
   } 

   // return first name
   public String getFirstName() {
   
      return firstName;
   } 

   // return last name
   public String getLastName() {
   
      return lastName;
   } 

   // return social security number
   public String getSocialSecurityNumber() {
   
      return socialSecurityNumber;
   } 

   public Date getDate() {
       return birthDate;
   }

   // return String representation of Employee object
   @Override
   public String toString() {
   
      return String.format("%s %s%nsocial security number: %s%nbirth date: %d/%d/%d", 
         getFirstName(), getLastName(), getSocialSecurityNumber(), birthDate.getMonth(), birthDate.getDay(), birthDate.getYear());
   } 

   // abstract method must be overridden by concrete subclasses
   public abstract double earnings(); 
     // no implementation here
}
