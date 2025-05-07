#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    	ofstream outFile("config.txt");
    	if (!outFile) {
        	cerr << "Cannot create file." << endl;
        	return 1;
    	}

    	outFile << "AAAAABBBBBCCCCC";
    	outFile.close();

    	fstream file("config.txt", ios::in | ios::out);
    	if (!file) {
        	cerr << "Error: Cannot open file for updating." << endl;
        	return 1;
    	}

    	file.seekp(5);
    	file << "XXXXX";
    	file.close();

   	ifstream inFile("config.txt");
    	string result;
    	getline(inFile, result);
    	inFile.close();

    	cout << "Updated content: " << result << endl;

    	return 0;
}
