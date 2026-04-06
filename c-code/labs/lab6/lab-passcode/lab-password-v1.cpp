#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

//a very simple program to check password

int get_number(){
    srand(time(NULL));
    int new_number = rand()%100+1;
    return new_number;
} 

void game()
{
    cout << "Let's play a simple game - guess a number" <<endl;
    cout << "Guess a number (1-100)" <<endl;
    cout << "You have 6 chances!" <<endl;

    int user_number;
    int target_number = get_number();

    for(int i=5; i>=0; i--){
        cout << "What is your guess? " <<endl;
        cin >> user_number;
 	if (target_number == user_number){
	    cout << "Good! That's the target number!" <<endl;
            break;
	}
	else if (target_number > user_number){
	    cout << "Too small!\n";
	}
	else{
	    cout << "Too big!" <<endl; 
	}
    }
    cout << "You lose the game..." <<endl;
   
}

int main() {

    int user_input;

    int pass1 = 345012;
    int pass2 = 789456;

    cout << "Do you know the passcode? enter the passcode: "<<endl;
    cin >> user_input;

    if (user_input == pass2){
	cout << "Correct passcode!" <<endl;
    }
    else{
	cout << "wrong passcode!\n" ;
	cout << "Hint: the passcode has been hard coded in the program!\n";
	cout << "Exit the program..." <<endl;
        exit(0);
    }

    game();    
    return 0;
}
