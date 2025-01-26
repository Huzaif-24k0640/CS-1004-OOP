#include <iostream>
#include <string>
using namespace std;

const int MAX = 5;


// Task 01


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


// Task 02


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


// Task 03


int calculateTotalDonations (string eventOne [], string eventTwo []) 
{
    	int totalDonations = 0;

    	for (int i = 0; i < MAX; i++) 
	{
        	if (eventOne [i].empty() == 0)
		{
			 totalDonations += 10;
		}//end if
        	if (eventTwo [i].empty() == 0) 
		{
			totalDonations += 10;
		}//end if
    	}//end for
    	return totalDonations;
}//calculate total donations


// Task 04


void reverseNamesDisplay (string event [], string eventName) 
{
	cout << "\nNames of participants of " << eventName << " in reverse order:\n";
    	for (int i = MAX - 1; i >= 0; i--)
	{
        	if (event [i].empty() == 0) 
		{
            		cout << event [i] << endl;
        	}//end if
    	}//end for
}//end function reverse names display


// Task 05


void barChartDisplay (int eventOneCount, int eventTwoCount) 
{
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
}//end bar chart display

int main () 
{
    string eventOne [MAX], eventTwo [MAX];

    eventRegistration (eventOne, eventTwo);

    checkAttendance (eventOne, eventTwo);

    int totalDonations = calculateTotalDonations(eventOne, eventTwo);
    cout << "\nTotal donations collected: $" << totalDonations << endl;

    reverseNamesDisplay (eventOne, "First event");
    reverseNamesDisplay (eventTwo, "Second event");

    barChartDisplay (MAX, MAX);

    return 0;
}
