#include <iostream>
#include <string>
using namespace std;

const int MAX = 5;

void eventRegistration (string eventOne [], string eventTwo []) 
{
    	cout << "\nEnter name of participants for first Event:\n";
    	for (int i = 0; i < MAX; i++) 
    	{
        	cout << "\nEnter name of participant " << i + 1 << ": ";
        	cin >> eventOne[i];
    	}//end for

    	cout << "\nEnter name of participants for second Event:\n";
    	for (int i = 0; i < MAX; i++) 
    	{
        	cout << "\nEnter name of participant " << i + 1 << ": ";
		cin >> eventTwo [i];
	}//end for

	return;
}//end event registration

int main ()
{
    	string eventOne [MAX], eventTwo [MAX];
    	eventRegistration (eventOne, eventTwo);

	return 0;
}//end main
