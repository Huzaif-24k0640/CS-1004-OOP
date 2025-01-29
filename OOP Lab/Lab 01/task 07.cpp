#include <iostream>
#include <string>
using namespace std;

const int CITIES = 4;
const int DAYS_IN_WEEK = 7;

void inputAQI(int aqi[CITIES][DAYS_IN_WEEK]) 
{
    	string cities[CITIES] = {"City 1", "City 2", "City 3", "City 4"};
    	cout << "\nEnter AQI values for each city over 7 days:\n";
    	for (int i = 0; i < CITIES; i++) 
	{
        	cout << "\n" << cities[i] << ":\n";
        	for (int j = 0; j < DAYS_IN_WEEK; j++) 
		{
            		cout << "Day " << (j + 1) << ": ";
            		cin >> aqi[i][j];
        	}//end for
    	}//end for
	return;
}//end function

void identifyCriticalDays(const int aqi[CITIES][DAYS_IN_WEEK]) 
{
    	cout << "\nCritical Pollution Days where (AQI > 150):\n" << endl;
    	for (int i = 0; i < CITIES; i++) {
        	cout << "City " << (i + 1) << ": ";
        	for (int j = 0; j < DAYS_IN_WEEK; j++) 
		{
            		if (aqi[i][j] > 150) {
                	cout << "Day " << (j + 1) << " ";
            		}//end if
        	}//end for
        	cout << endl;
    	}//end for
}//end function

int main ()
{
    	int aqi[CITIES][DAYS_IN_WEEK];
    	float weeklyAvg[CITIES][2] = {0}; 

	inputAQI(aqi);
    	identifyCriticalDays(aqi);

	return 0;
}//end main
