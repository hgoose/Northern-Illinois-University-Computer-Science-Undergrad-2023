/*
CSCI 240 Fraction Class daily Part 2
*/


#include <iostream>
#include <iomanip>

using namespace std;


class Fraction
{
public:
  Fraction();
  Fraction( int, int );
  
  void display();

  void setNumerator( int );
  void setDenominator( int );
  void setFraction( int, int );

  int getNumerator();
  int getDenominator();
  
  Fraction divide( int, int );
  Fraction divide( Fraction& );

private:
  int numerator;
  int denominator;
  
  int GCD( int, int );
  void reduce();

};



int main()
  {
  Fraction result;

  int test_num;
  
  cout << "Test number? ";
  cin >> test_num;

  //test the divide method that takes two integers as arguments
  if(test_num == 1)
    {
    Fraction fraction1(8, 7),
             fraction2(2, 18);

    cout << endl << "***** Testing the divide method with two integers *****"
         << endl << endl;

    //8/7 / 5/8
    fraction1.display();
  
    cout << " / 5/8 = ";

    result = fraction1.divide(5, 8); 
    result.display();
    cout << endl << endl;
  
    //2/18 / 5/15
    fraction2.display();

    cout << " / 5/15 = ";

    result = fraction2.divide(5, 15);
    result.display();
    cout << endl << endl;

    //result / 3/11
    result.display();

    cout << " / 3/11 = ";
  
    result = result.divide(3, 11);
    result.display();
	}
  //test the divide method that takes a Fraction object as an argument
  else if(test_num == 2)
    {
    Fraction fraction3(8, 7),
             fraction4(108, 511),
             fraction5(5, 8),
			 fraction6(4,63);

    cout << endl << "***** Testing the divide method with Fraction object *****"
         << endl << endl;


    //8/7 /  8/7
    fraction3.display();
    cout << " / ";
    fraction3.display();
    cout << " = ";
  
    result = fraction3.divide(fraction3);
  
    result.display();
    cout << endl << endl;
  
    //fraction4 /  fraction5
    fraction4.display();
    cout << " / ";
    fraction5.display();
    cout << " = ";

    result = fraction4.divide(fraction5);

    result.display();
    cout << endl << endl;
  
    //fraction6 /  fraction4
    fraction6.display();
    cout << " / ";
    fraction4.display();
    cout << " = ";

    result = fraction6.divide(fraction4);

    result.display();
	}
  //test both divide methods
  else if(test_num == 3)
    {
    Fraction fraction7(15, 32),
             fraction8(2, 1),
             fraction9(7, 6);

    cout << endl << "***** Testing the divide method with Fraction object *****"
         << endl << endl;


    //fraction7 /  fraction8
    fraction7.display();
    cout << " / ";
    fraction8.display();
    cout << " = ";
  
    result = fraction7.divide(fraction8);
  
    result.display();
    cout << endl << endl;
  
    //fraction9 /  fraction7
    fraction9.display();
    cout << " / ";
    fraction7.display();
    cout << " = ";

    result = fraction9.divide(fraction7);

    result.display();
    cout << endl << endl;

    cout << endl << "***** Testing the divide method with two integers *****"
         << endl << endl;
  
    //fraction9 / 6/7
    fraction9.display();
    cout << " / 6/7 = ";

    result = fraction9.divide(6, 7);

    result.display();
    cout << endl << endl;

    //result / 9/7
    result.display();
    cout << " / 9/7 = ";

    result = result.divide(9, 7);

    result.display();
	}
  //test divide methods with values entered by the user
  else
    {
    int numerator, denominator;
    
    //Get the numerator and denominator from the user
    cout << "Numerator? ";
    cin >> numerator;
    
    cout << "Denominator? ";
    cin >> denominator;
    
    //Create a fraction object using the input values and
    //one with the default constructor
    Fraction fraction10( numerator, denominator );
    Fraction fraction11;
    
    cout << endl << "***** Testing the divide method with Fraction object *****"
         << endl << endl;

    //user fraction / 1/1
    fraction10.display();
    cout << " / ";
    fraction11.display();
    cout << " = ";

    result = fraction10.divide(fraction11); 
    result.display();
    cout << endl << endl;

    //Get another numerator and denominator from the user
    cout << "Numerator? ";
    cin >> numerator;
    
    cout << "Denominator? ";
    cin >> denominator;

    //update fraction11 with the new input values
    fraction11.setFraction(numerator, denominator);
  
    cout << endl << "***** Testing the divide method with two integers *****"
         << endl << endl;

    //user fraction / 5/8
    fraction11.display();
    cout << " / 5/8 = ";

    result = fraction11.divide(5, 8); 
    result.display();
    }


  cout << endl << endl;
  
  return 0;
  }



//************************************************************
//* Class Constructors
//*
//* Fraction()
//* Default constructor that creates an object with numerator 1
//* and denominator 1
//*
//* Fraction(int, int)
//* Constructor that creates an object with specific numerator
//* and denominator values. The fraction is saved in reduced
//* form
//************************************************************

Fraction::Fraction() {
    numerator = 1;
  {
  denominator = 1;
  }
}

Fraction::Fraction( int initNum, int initDen )
  {
  setFraction(initNum, initDen);
  }



//************************************************************
//* void display()
//* Method that displays the fraction object
//************************************************************
  
void Fraction::display()
  {
  cout << numerator << "/" << denominator;
  }



//************************************************************
//* set Methods
//*
//* void setNumerator(int)
//* Method that changes the numerator data member and reduces
//* the fraction
//*
//* void setDenominator(int)
//* Method that changes the denominator data member and reduces
//* the fraction
//*
//* void setFraction(int, int)
//* Method that changes both the numerator and denominator data

//* members and reduces the fraction
//************************************************************
void Fraction::setNumerator( int newNumerator )
  {
  numerator = newNumerator;
  reduce();
  }


void Fraction::setDenominator( int newDenominator )
  {
  denominator = newDenominator;
  reduce();
  }
  
  
void Fraction::setFraction( int newNumerator, int newDenominator )
  {
  numerator = newNumerator;
  denominator = newDenominator;
  
  reduce();
  }



//************************************************************
//* get Methods
//*
//* int getNumerator()
//* Method that returns the numerator data member
//*
//* int getDenominator()
//* Method that returns the denominator data member
//************************************************************

int Fraction::getNumerator()
 {
 return numerator;
 }


int Fraction::getDenominator()
 {
 return denominator;
 }


//************************************************************
//* void reduce()
//*
//* Method that uses the greatest common divisor to reduce a
//* fraction
//************************************************************

void Fraction::reduce()
  {
  int gcd = GCD(numerator, denominator);
  
  numerator = numerator / gcd;
  denominator = denominator / gcd;
  }



//************************************************************
//* int GCD(int, int)
//*
//* Method that finds the greatest common divisor of two integers
//************************************************************

int Fraction::GCD( int num1, int num2 )
  {
  int gcd, remainder;

  gcd = num2;
  remainder = num1 % gcd;

  //continuously divide until the remainder is 0
  while( remainder != 0 )
    {
    num1 = gcd;
    gcd = remainder;

    remainder = num1 % gcd;
    }

  return gcd;
}

Fraction Fraction::divide(int divNumerator, int divDenominator) {
    return Fraction(this->getNumerator() * divDenominator, this->getDenominator() * divNumerator);
}

Fraction Fraction::divide(Fraction& divvalue) {
    return Fraction(this->getNumerator() * divvalue.getDenominator(), this->getDenominator() * divvalue.getNumerator());

}


