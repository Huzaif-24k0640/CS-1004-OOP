#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    	ofstream outFile("large_log.txt");
    	outFile << "This is the first part of the log.\n";
    	outFile << "This is the second part of the log.\n";
    	outFile << "And the third part.";
    	outFile.close();

    	ifstream inFile("large_log.txt");
    	if (!inFile) {
        	cerr << "Cannot open file for reading." << endl;
        	return 1;
    	}

    	char buffer[11];r
    	inFile.read(buffer, 10);
    	buffer[10] = '\0';
    	cout << "First 10 chars: \"" << buffer << "\"" << endl;
    	streampos pos1 = inFile.tellg();
    	cout << "Read position after first block: " << pos1 << endl;

    	inFile.read(buffer, 10);
    	buffer[10] = '\0';
    	cout << "Next 10 chars: \"" << buffer << "\"" << endl;
    	streampos pos2 = inFile.tellg();
    	cout << "Read position after second block: " << pos2 << endl;

    	inFile.close();
    	return 0;
}
