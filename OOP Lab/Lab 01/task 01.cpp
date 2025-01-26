#include <iostream>
#include <string>
using namespace std;

void eventRegistration (string arr[])
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Enter name of " << i + 1 << " participant: ";
		cin >> arr[i];
		cout << endl;
	}
}

int main ()
{
	string eventOne[5];
	string eventTwo[5];
  
  //for first event
	cout << "\nEvent one registration:\n" << endl;
	eventRegistration (eventOne);

  //for second event 
	cout << "\nEvent two registration:\n" << endl;
	eventRegistration (eventOne);
	
	return 0;
}
