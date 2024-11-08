//CSCI 240 - Basic NIU_Student Class Daily

#include <iostream>
#include <iomanip>

using namespace std;

class NIU_Student
  {
  private:
    string ZID;

  public:

    NIU_Student();               // Default Constructor
    NIU_Student(string);         // Alternative Constructor


    void print();                //Display the student information

    void setZID(string);         //Change the student's id number
    string getZID();             //Return the student's id number
  };


int main()
  {
  int test_num;
  
  cout << "Test number? ";
  cin >> test_num;

  //create an object and test different methods based on test number
  if(test_num == 1)
    {
    NIU_Student student1;    //using default constructor
    
    cout << endl << endl << "Test 1: test default constructor and print method"
         << endl << endl << "The student id number is \'";

    student1.print();
    cout << "\'" << endl;
    }
  else if(test_num == 2)
    {
    NIU_Student student2;    //using default constructor
    
    cout << endl << endl << "Test 2: test default constructor, setZID, and print methods"
         << endl << endl << "The student initial id number is \'";
    student2.print();
    cout << "\'" << endl;
    
    student2.setZID("z1234567");

    cout << endl << "After using setZID, the student id number is now \'";

    student2.print();
    cout << "\'" << endl;    
    }
  else if(test_num == 3)
    {
    NIU_Student student3("z9887665");    //using alternate constructor
    
    cout << endl << endl << "Test 3: test alternate constructor and print method"
         << endl << endl << "The student id number is \'";
    student3.print();
    cout << "\'" << endl;
    }
  else if(test_num == 4)
    {
    NIU_Student student4("z1223445");    //using alternate constructor
    
    cout << endl << endl << "Test 4: test alternate constructor, setZID, and getZID methods"
         << endl << endl << "The student id number is \'" << student4.getZID() << "\'" << endl;
    
    student4.setZID("z2468013");

    cout << endl << "After using setZID, the student id number is now \'"
         << student4.getZID() << "\'" << endl;
    }
  else if(test_num == 5)
    {
    NIU_Student student5("z1245780");    //using alternate constructor
    NIU_Student student6;                //using default constructor

    cout << endl << endl << "Test 5: test both constructors and all methods"
         << endl << endl << "The 1st student id number is \'";
    student5.print();
    cout << "\'" << endl << "The 2nd student id number is \'";
    student6.print();
    cout << "\'" << endl;
    
    student6.setZID(student5.getZID());

    cout << endl << "After using getZID on the 1st student and setZID on the 2nd student";

    cout << endl << endl << "The 1st student id number is \'";
    student5.print();
    cout << "\'" << endl << "The 2nd student id number is \'";
    student6.print();
    cout << "\'" << endl;
    }
  else
    {
    string z_number;
    
    cout << "What is the z_number? ";
    cin >> z_number;
    
    NIU_Student student7(z_number);    //using alternate constructor

    cout << endl << endl << "Test 6: get z-number from user input"
         << endl << endl << "The student id number is \'";
    student7.print();
    cout << "\'" << endl;
    }

  return 0;
  }



//Code the constructors and methods below this line
NIU_Student::NIU_Student() : ZID("") {}
NIU_Student::NIU_Student(string ZID) {
    this->ZID = ZID;
}

void NIU_Student::print() {
    cout << this->ZID; 
}
void NIU_Student::setZID(string ZID) {
    this->ZID = ZID;

}
string NIU_Student::getZID() {

    return this->ZID;
}



