#include <string>
#include <iostream>

using namespace std;

int roman_to_decimal (const string& roman_value)
{
  int numval = 0;

  for (size_t i = 0; i < roman_value.length(); i++)
    {
      if (roman_value[i] == 'M')
	{
	  numval += 1000;
	  if (roman_value[i - 1] == 'C')
	    {
	      numval -= 200;
	    }
	}
      else if (roman_value[i] == 'D')
	{
	  numval += 500;
	  
	  if (roman_value[i - 1] == 'C')
	    {
	      numval -= 200;
	    }
	}
      else if (roman_value[i] == 'C')
	{
	  numval += 100;

	  if (roman_value[i - 1] == 'X')
	    {
	      numval -= 20;
	    }
	}
      else if (roman_value[i] == 'L')
	{
	  numval += 50;
	  if (roman_value[i - 1] == 'X')
	    {
	      numval -= 20;
	    }
	}
      else if (roman_value[i] == 'X')
	{
	  numval += 10;
	  if (roman_value[i - 1] == 'I')
	    {
	      numval -= 2;
	    }
	}
      else if (roman_value[i] == 'V')
	{
	  numval += 5;
	  if (roman_value[i - 1] == 'I')
	    {
	      numval -= 2;
	    }
	}
      else if (roman_value[i] == 'I')
	{
	  numval += 1;
	}
     
    }



  return numval;
}
