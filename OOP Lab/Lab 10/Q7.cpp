#include <iostream>
#include <fstream>
using namespace std;

int main() {
    	ofstream outFile("sensor_log.txt");

    	if (!outFile) {
        	cerr << "Could not open file for writing." << endl;
        	return 1;
    	}

    	outFile << "Sensor 1: 25.5 C\n";
    	streampos pos1 = outFile.tellp();
    	cout << "Write position after first line: " << pos1 << endl;

    	outFile << "Sensor 2: 98.1 %RH\n";
    	streampos pos2 = outFile.tellp();
    	cout << "Write position after second line: " << pos2 << endl;

    	outFile.close();
    	return 0;
}
