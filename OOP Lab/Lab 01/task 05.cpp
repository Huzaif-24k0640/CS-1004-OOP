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

void reverseNamesDisplay (string event [], string eventName) 
{
	cout << "\nNames of participants of " << eventName << " in reverse order:\n";
    	for (int i = MAX - 1; i >= 0; i--)
	{
        	if (event [i] != "-") 
		{
            		cout << event [i] << endl;
        	}//end if

    	}//end for

	return;
}//end function reverse names display

void barChartDisplay (string eventOne [], string eventTwo []) 
{
	int eventOneCount = 0, eventTwoCount = 0;
	for (int i = 0; i < 5; i++)
	{
		if (eventOne [i] != "-")
		{
			eventOneCount++;
			cout << eventOneCount;
		}//end if
		
		if (eventTwo [i] != "-")
		{
			eventTwoCount++;
			cout << eventOneCount;
		}//end if

	}//end for

	cout << "\nEvent Popularity Bar Chart:\n" << endl;
    	cout << "First event: ";
    	for (int i = 0; i < eventOneCount; i++) 
	{
        	cout << "*";
    	}//end for

    	cout << " (" << eventOneCount << " participants)\n";
    	cout << "\nSecond event: ";
    	for (int i = 0; i < eventTwoCount; i++) 
	{
        	cout << "*";
    	}//end for

    	cout << " (" << eventTwoCount << " participants)\n";
	return;
}//end bar chart display

int main ()
{
    	string eventOne [MAX], eventTwo [MAX];

    	eventRegistration (eventOne, eventTwo);

    	barChartDisplay (eventOne, eventTwo);

	return 0;
}//end main
