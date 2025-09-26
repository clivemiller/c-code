#include <iostream>
#include <climits>
#include <limits>

using namespace std;

//clear the buffer used for cin
void clearbuffer()
{
  cin.clear();  //clear the error flag on cin
  cin.ignore(numeric_limits<streamsize>::max(), '\n');  //skips up to numeric_limits<streamsize>::max() characters or until a new line is encountered
}


int main(){

  cout << "---------------------- Task 1--------------------------" <<endl;
  cout << " Know the range of each data type: " <<endl<<endl;


  cout << "char: sizeof(char) is " << sizeof(char) << " bytes" << endl;
  cout << "\tmax is " << CHAR_MAX << ", min is " <<CHAR_MIN << endl;
  cout << "short: sizeof(short) is " << sizeof(short) << " bytes" << endl;
  cout << "\tmax is " << SHRT_MAX << ", min is " <<SHRT_MIN << endl;
  cout << "int: sizeof(int) is " << sizeof(int) << " bytes" << endl;
  cout << "\tmax is " << INT_MAX << ", min is " <<INT_MIN << endl;
  cout << "long: sizeof(long int) is " << sizeof(long int) << " bytes" << endl;
  cout << "\tmax is " << LONG_MAX << ", min is " <<LONG_MIN << endl;
  cout << "long long: sizeof(long long int) is " << sizeof(long long int) << " bytes" << endl;
  cout << "\tmax is " << LLONG_MAX << ", min is " <<LLONG_MIN << endl;

  cout << "u_char: sizeof(unsigned char) is " << sizeof(unsigned char) << " bytes" << endl;
  cout << "\tmax is " << UCHAR_MAX << ", min is " << 0 << endl;
  cout << "u_short: sizeof(unsigned short) is " << sizeof(unsigned short) << " bytes" << endl;
  cout << "\tmax is " << USHRT_MAX << ", min is " << 0 << endl;
  cout << "u_int: sizeof(unsigned int) is " << sizeof(unsigned int) << " bytes" << endl;
  cout << "\tmax is " << UINT_MAX << ", min is " << 0 << endl;
  cout << "u_long: sizeof(unsigned long int) is " << sizeof(unsigned long int) << " bytes" << endl;
  cout << "\tmax is " << ULONG_MAX << ", min is " << 0 << endl;
  cout << "u_long long: sizeof(unsigned long long int) is " << sizeof(unsigned long long int) << " bytes" << endl;
  cout << "\tmax is " << ULLONG_MAX << ", min is " << 0 << endl;


   cout << "\n\n--------------------------TASK 2----------------------------\n";
  
    cout << " -------- singed int ------------\n";
    int num;
    cout << "num is declared as a signed int (" << sizeof(int) << "  bytes - MAX: " << INT_MAX << " MIN: " << INT_MIN << " )" << endl;
    cout << "The default assignment is: num = 2147483999 \n";
    num = 2147483999;
    cout << "After the assignment, the value stored in num is: " << num << endl;
    cout << "Now give it a value, first run? just type 2147483999" << endl;
    cout << "You input is: ";
    cin >> num;
    cout << "The value stored in num is: " << num << endl;
    clearbuffer();

    cout << "\n -------- unsinged int ------------\n";
    unsigned int u_num;    
    cout << "u_num is declared as a unsigned int( " << sizeof(unsigned int) << " bytes - MAX: " << UINT_MAX << " MIN: 0 )" << endl;
    cout << "The default assignment is: u_num = 5000000000 \n";
    u_num =5000000000;
    cout << "After the assignment, the value stored in u_num is: " << u_num << endl;
    cout << "Now it is your turn, your input is: ";
    cin >> u_num;
    cout << "The value stored in u_num is: " << u_num << endl;
    clearbuffer();

    cout << "\n -------- singed short ------------\n";
    short short_num; 
    cout << "short_num is declared as a signed short ( " << sizeof(short) << " bytes - MAX: " << SHRT_MAX << " MIN: " << SHRT_MIN << " )" << endl;
    cout << "The default assignment is: short_num = -50000 \n";
    short_num = -50000;
    cout << "After the assignment, the value stored in short_num is: " << short_num << endl;
    cout << "Now give it a value, your input is: ";
    cin >> short_num;
    cout << "The value stored in short_num is: " << short_num << endl;
    clearbuffer();

    cout << "\n -------- unsinged short ------------\n";
    unsigned short u_short_num;
    cout << "u_short_num is declared as a unsigned short ( " << sizeof(unsigned short) << " bytes - MAX: " << USHRT_MAX << " MIN: 0 )" << endl;
    cout << "The default assignment is: u_short_num = -50 \n";
    u_short_num = -50;
    cout << "After the assignment, the value stored in u_short_num is: " << u_short_num << endl;
    cout << "Now you give a value to it: ";
    cin >> u_short_num;
    cout << "The value stored in u_short_num is: " << u_short_num << endl;
    clearbuffer();

   cout << "\n\n--------------------------TASK 3----------------------------\n";
    
  
  //1a
   
  short x_short = 20000;
  short y_short = 20000;
  cout << "1a. x + y = " << x_short+y_short << endl;

  //1b

    x_short = 20000; 
    y_short = 20000; 
    short z_short = x_short + y_short; 
    cout << "1b. short z_short = " << z_short << endl; 

    //1c 
    x_short = 20000; 
    y_short = 20000; 
    int z1_int = x_short + y_short; 
    cout << "1c. int z1_int = " << z1_int << endl; 

    //1d
    x_short = 20000; 
    y_short = 20000;
    int z2_int = (int)x_short + (int)y_short; 
    cout << "1d. int z2_int = " << z2_int << endl;
  

    //example 2a 
    int x_int = 2000000000; 
    int y_int = 2000000000; 
    cout << "2a. x_int + y_int = " << x_int + y_int << endl;

    //example 2b 
    x_int = 2000000000; 
    y_int = 2000000000; 
    int z_int = x_int + y_int; //z is out of range now 
    cout << "2b. z_int = " << z_int << endl; 
    
    //example 2c 
    x_int = 2000000000; 
    y_int = 2000000000; 
    long long z1_ll = x_int + y_int; 
    cout << "2c. long long z1_ll = " << z1_ll << endl;


    //example 2d 
    x_int = 2000000000; 
    y_int = 2000000000;
    long long z2_ll = (long long)x_int + (long long)y_int; 
    cout << "2d. long long z2_ll = " << z2_ll << endl;


    //example 3a
    long long  x_ll = 2000000000; 
    long long  y_ll = 2000000000; 
    cout << "3a. x_ll + y_ll = " << x_ll + y_ll << endl;
    
    //example 3b
    x_int = 2000000000; 
    y_ll = 2000000000;
    long long z3_ll = x_int + y_ll; 
    cout << "3b. long long z3_ll = " << z3_ll << endl;

  
 
}
