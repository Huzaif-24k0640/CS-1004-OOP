#include <iostream>
#include <string>
using namespace std;

const int CITIES = 4;
const int DAYS_IN_WEEK = 7;
const int DAYS_IN_MONTH = 28;

void inputAQI(int aqi[CITIES][DAYS_IN_MONTH]) 
{
    	string cities[CITIES] = {"City 1", "City 2", "City 3", "City 4"};
    	cout << "\nEnter AQI values for each city over 28 days:\n";
    	for (int city = 0; city < CITIES; city++) 
	{
        	cout << "\n" << cities[city] << ":\n";
        	for (int day = 0; day < DAYS_IN_MONTH; day++) 
		{
            		cout << "Day " << (day + 1) << ": ";
            		cin >> aqi[city][day];
        	}//end for
    	}//end for
}//end function

void calculateWeeklyAverages(int aqi[CITIES][DAYS_IN_MONTH], double weeklyAvg[CITIES][4]) {
    for (int city = 0; city < CITIES; city++) {
        for (int week = 0; week < 4; week++) {
            int sum = 0;
            for (int day = 0; day < DAYS_IN_WEEK; day++) {
                sum += aqi[city][week * DAYS_IN_WEEK + day];
            }
            weeklyAvg[city][week] = sum / 7.0;
        }
    }
}

void monthlyAQIAnalysis(int aqi[CITIES][DAYS_IN_MONTH]) 
{
    	double monthlyAvg[CITIES] = {0}, firstWeekAvg[CITIES] = {0}, lastWeekAvg[CITIES] = {0};
    	int minDropCity = 0;
    	double maxDrop = 0;

    	for (int city = 0; city < CITIES; city++) 
	{
        	double sum = 0;
        	for (int day = 0; day < DAYS_IN_MONTH; day++) 
		{
            		sum += aqi[city][day];
        	}
        	monthlyAvg[city] = sum / DAYS_IN_MONTH;

        	for (int day = 0; day < DAYS_IN_WEEK; day++) 
		{
            		firstWeekAvg[city] += aqi[city][day];
            		lastWeekAvg[city] += aqi[city][DAYS_IN_MONTH - 7 + day];
        	}
        	firstWeekAvg[city] /= 7;
        	lastWeekAvg[city] /= 7;

        	double drop = firstWeekAvg[city] - lastWeekAvg[city];
        	if (drop > maxDrop) 
		{
            		maxDrop = drop;
            		minDropCity = city;
        	}
    	}

    	cout << "\nCity with the most improved air quality: City " << (minDropCity + 1) << " (Drop: " << maxDrop << " AQI points)\n";
}

void identifyCriticalDays(int aqi[CITIES][DAYS_IN_MONTH]) 
{
    	cout << "\nCritical Pollution Days:\n";
    	for (int city = 0; city < CITIES; city++) 
	{
        	cout << "City " << (city + 1) << ": ";
        	for (int day = 0; day < DAYS_IN_MONTH; day++) 
		{
            		if (aqi[city][day] > 150) 
			{
                	cout << "Day " << (day + 1) << " ";
            		}
        	}
        	cout << endl;
    	}
}

void generateReport(int aqi[CITIES][DAYS_IN_MONTH], double weeklyAvg[CITIES][4])
{
    	cout << "\n--- Air Quality Report ---\n";

    	cout << "\nWeekly AQI Averages:\n";
    	for (int city = 0; city < CITIES; city++) 
	{
        	cout << "City " << (city + 1) << ": ";
        	for (int week = 0; week < 4; week++) 
		{
            		cout << weeklyAvg[city][week] << " ";
        	}
        	cout << endl;
    	}

    	identifyCriticalDays(aqi);

    	int highestAQI = 0, lowestAQI = 1000;
    	for (int city = 0; city < CITIES; city++) 
	{
        	for (int day = 0; day < DAYS_IN_MONTH; day++) 
		{
            		if (aqi[city][day] > highestAQI) highestAQI = aqi[city][day];
            			if (aqi[city][day] < lowestAQI) lowestAQI = aqi[city][day];
        	}
    	}

    	cout << "\nHighest AQI recorded: " << highestAQI;
    	cout << "\nLowest AQI recorded: " << lowestAQI << "\n";
}


int main() {
    int aqi[CITIES][DAYS_IN_MONTH]; 
    double weeklyAvg[CITIES][4] = {0}; 

    inputAQI(aqi);
    calculateWeeklyAverages(aqi, weeklyAvg);
    monthlyAQIAnalysis(aqi);
    generateReport(aqi, weeklyAvg);

    return 0;
}
