#include <iostream>
#include <string>
using namespace std;

const int MAX = 5;

void eventRegistration (string eventOne [], string eventTwo []) 
{
    	cout << "\nEnter name of participants for first Event:\n";
    	for (int i = 0; i < MAX; i++) 
    	{
        	cout << "\nEnter name of participant " << i + 1 << "('-' for vacant): ";
        	cin >> eventOne[i];
    	}//end for

    	cout << "\nEnter name of participants for second Event:\n";
    	for (int i = 0; i < MAX; i++) 
    	{
        	cout << "\nEnter name of participant " << i + 1 << "('-' for vacant): ";
		cin >> eventTwo [i];
	}//end for

	return;
}//end event registration

void checkAttendance (string eventOne [], string eventTwo [])
{
    	string name;
    	bool found = false;

    	cout << "\nEnter the name to check for attendance: ";
    	cin >> name;

    	for (int i = 0; i < MAX; i++) {
        	if (eventOne [i] == name || eventTwo [i] == name) 
		{
            		found = true;
            		break;
        	}//end if

    	}//end for

    	if (found) 
	{
        	cout << "\n" << name << " is registered in one of the events.\n";
    	} else {
        	cout << "\n" << name << " is not registered in any event.\n";
    	}//end if else

	return;
}//end check attendance

int calculateTotalDonations (string eventOne [], string eventTwo []) 
{
    	int totalDonations = 0;

    	for (int i = 0; i < MAX; i++) 
	{
        	if (eventOne [i] != "-")
		{
			 totalDonations += 10;
		}//end if

        	if (eventTwo [i] != "-") 
		{
			totalDonations += 10;
		}//end if

    	}//end for

    	return totalDonations;
}//calculate total donations

int main ()
{
    	string eventOne [MAX], eventTwo [MAX];
    	eventRegistration (eventOne, eventTwo);

    	int totalDonations = calculateTotalDonations(eventOne, eventTwo);
    	cout << "\nTotal donations collected: $" << totalDonations << endl;

	return 0;
}//end main
