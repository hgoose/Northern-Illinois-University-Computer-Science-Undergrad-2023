#!/usr/bin/env python3

# Week 4 Homework Program
# Author: Nate Warner
# Date: 9/15/2022

# Includes
import os

# Formating output  
def FormatOutput():
    """ Format Output """

    #Series of prints for output stream
    print("{0:11s} {1:11s} {2:12s} {3:15s}".format("Make" , "Model" , "Units Sold", "Starting Price"))
    print("{0:11s} {1:12s} {2:>9,d} {3:>16,.2f}".format("Chevorlet" , "Silverado" , 586675 , 28595))
    print("{0:11s} {1:10s} {2:>11,d} {3:>16,.2f}".format("Chevrolet" , "Equinox" , 270994 , 25000)) 
    print("{0:11s} {1:11s} {2:>10,d} {3:>16,.2f}".format("Ford" , "F-Series" , 787422 , 30635))     
    print("{0:11s} {1:9s} {2:>12,d} {3:>16,.2f}".format("GMC" , "Sierra", 253016 , 29695)) 
    print("{0:11s} {1:9s} {2:>12,d} {3:>16,.2f}".format("Honda" , "CR-V" , 333502 , 26525)) 
    print("{0:11s} {1:9s} {2:>12,d} {3:>16,.2f}".format("Honda" , "Civic" , 261225 , 22000)) 
    print("{0:6s} {1:9s} {2:>12,d} {3:>16,.2f}".format("Lamborghini" , "Huracan" , 1095 , 208571)) 
    print("{0:11s} {1:9s} {2:>12,d} {3:>16,.2f}".format("Toyota" , "RAV4" , 430387 , 27325)) 
    print("{0:11s} {1:9s} {2:>12,d} ${3:>16,.2f}".format("Toyota" , "Camry" , 294348 , 25965))

def FormatCleaner():
    """ Easy """

    print(
 """
Make	      Model	       Units Sold	 Starting Price
Chevrolet     Silverado           586,675	     $28,595.00
Chevrolet     Equinox	          270,994	     $25,000.00
Ford	      F-Series	          787,422	     $30,635.00
GMC	      Sierra	          253,016	     $29,695.00
Honda	      CR-V	          333,502	     $26,525.00
Honda	      Civic	          261,225	     $22,000.00
Lamborghini   Huracan	            1,095	    $208,571.00
Toyota	      RAV4	          430,387	     $27,325.00
Toyota	      Camry	          294,348	     $25,965.00
"""
    )

def main():
    # Clears Screen in shell
    os.system("clear") # Linux console clear
    os.system("cls") # Win

    #Funtion Calls
    FormatOutput()
    FormatCleaner()

    return 0;

if __name__ == '__main__':
    main()

