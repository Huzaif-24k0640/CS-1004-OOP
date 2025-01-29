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

void calculateWeeklyAverages(const int aqi[CITIES][DAYS_IN_WEEK], float weeklyAvg[CITIES][2]) 
{
    	for (int i = 0; i < CITIES; i++) 
	{
            	int sum = 0;
        	for (int j = 0; j < DAYS_IN_WEEK; j++) 
		{
                	sum += aqi[i][j];
            		weeklyAvg[i][2] = sum / 7.0;
        	}//end for
		cout << "\nWeekly average for City " << (i + 1) << " is: " << weeklyAvg[i][2] << endl;
    	}//end for
}//end function

void findWorstCity(const float weeklyAvg[CITIES][2]) 
{
    	double highestAvg = 0;
    	int worstCityIndex = 0;
    	for (int i = 0; i < CITIES; i++) 
	{
        	if (weeklyAvg[i][2] > highestAvg) 
		{
            		highestAvg = weeklyAvg[i][2];
            		worstCityIndex = i;
        	}//end if
    	}//end for
    	cout << "\nCity with the worst air quality: City " << (worstCityIndex + 1) << " (Average AQI: " << highestAvg << ")\n";
}//end function

int main ()
{
    	int aqi[CITIES][DAYS_IN_WEEK];
    	float weeklyAvg[CITIES][2] = {0}; 

	inputAQI(aqi);
    	calculateWeeklyAverages(aqi, weeklyAvg);
    	findWorstCity(weeklyAvg);

	return 0;
}//end main
