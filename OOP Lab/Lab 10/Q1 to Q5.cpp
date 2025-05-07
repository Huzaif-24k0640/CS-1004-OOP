#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    	ifstream file("vehicles.txt");

    	if (!file.is_open()) {
    	    	cerr << "Could not open the file." << endl;
    	    	return 1;
    	}

    	string line;
	int count = 0;
    	
	while (getline(file, line)) {

        	cout << "-----------------------------" << endl;
		cout << "Data for: " << count + 1 << " vehicle." << endl;
        	cout << "-----------------------------" << endl;
		
		//Task 01
        	cout << "-----------------------------" << endl;
        	cout << line << endl;
        	cout << "-----------------------------" << endl;

		//Task 02
 		istringstream ss(line);
	        string type, id, name, yearStr, extraData, certification;

	        getline(ss, type, ',');
        	getline(ss, id, ',');
        	getline(ss, name, ',');
        	getline(ss, yearStr, ',');
        	getline(ss, extraData, ',');
        	getline(ss, certification, ',');

		//Task 03
        	int year = stoi(yearStr);

		//Task 04
 		size_t colonPos = extraData.find(':');
        	if (colonPos != string::npos) {
            		string valueStr = extraData.substr(colonPos + 1);

            		if (type == "AutonomousCar") {
                		float softwareVersion = stof(valueStr);
        			cout << "-----------------------------" << endl;
        			cout << "Vehicle ID: " << id << endl;
                		cout << "Software Version: " << softwareVersion << endl;
       				cout << "-----------------------------" << endl;
            		}
            		else if (type == "ElectricVehicle") {
                		int batteryCapacity = stoi(valueStr);
        			cout << "-----------------------------" << endl;
        			cout << "Vehicle ID: " << id << endl;
                		cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
        			cout << "-----------------------------" << endl;
            		}

			//Task 05
 	    		else if (type == "HybridTruck") {
            			size_t cargoPos = extraData.find("Cargo:");
            			size_t pipePos = extraData.find('|');
            			size_t batteryPos = extraData.find("Battery:");

            			if (cargoPos != string::npos && pipePos != string::npos && batteryPos != string::npos) {
        	        		string cargoStr = extraData.substr(cargoPos + 6, pipePos - (cargoPos + 6));
	                		int cargo = stoi(cargoStr);

                			string batteryStr = extraData.substr(batteryPos + 8);
                			int battery = stoi(batteryStr);
					
					cout << "-----------------------------" << endl;
                			cout << "Cargo Capacity: " << cargo << " kg" << endl;
                			cout << "Battery Capacity: " << battery << " kWh" << endl;
        				cout << "-----------------------------" << endl;
                		} else {
                			cout << "Error: Invalid ExtraData format for HybridTruck." << endl;
                		}
            		}
        	} else {
            		cout << "Warning: No ':' found in ExtraData field." << endl;
        	}

        	cout << "-----------------------------" << endl;
        	cout << "Type: " << type << endl;
        	cout << "ID: " << id << endl;
	        cout << "Name: " << name << endl;
        	cout << "Year (int): " << year << endl;
	        cout << "ExtraData: " << extraData << endl;
        	cout << "Certification: " << certification << endl;
        	cout << "-----------------------------" << endl;
	
		count++;
    	}

    	file.close();
    	return 0;
}
