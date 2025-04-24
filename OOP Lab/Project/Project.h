#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Person {
public:
	Person () {}
    
	virtual void registerUser () = 0;
    virtual bool loginUser () = 0;
    virtual void display () = 0;

	~Person () {}
};

class Admin : public Person {
private:
    string username;
	string password;

public:
    Admin () {}

    void setUsername (string u) { username = u; }
	void setPassword (string p) { password = p; }

    string getUsername () { return username; }
	string getPassword () { return password; }

    bool adminUsernameExists (string& usernameToCheck) {
    	ifstream file("admins.txt");
    	if (!file) {
    		cout << "Error: Could not open file for reading.\n" << endl;
    		return false;
    	}
		string storedUser, storedPass;

    	while (file >> storedUser >> storedPass) {
    		if (storedUser == usernameToCheck) {
    			cout << "Admin username already taken.\n";
      			return true;
       		}
   		}
		return false;
	}

	void registerUser () override {
		do {
       		cout << "Enter new admin username: ";
       		cin >> username;
   		} while (adminUsernameExists (username) != false);
        
		cout << "Enter new admin password: ";
       	cin >> password;

       	ofstream file ("admins.txt", ios::app);
       	file << username << " " << password << endl;
       	file.close();

       	cout << "Admin registration successful!\n";
   	}

	bool loginUser () override {
    	string u, p;
         	
		cout << "\nEnter admin username: ";
    	cin >> u;
    	cout << "Enter admin password: ";
    	cin >> p;

        ifstream file ("admins.txt");
    	string storedUser, storedPass;
    	bool found = false;

        while (file >> storedUser >> storedPass) {
    		if (storedUser == u && storedPass == p) {
                username = u;
        		found = true;
        		break;
    		}
    	}
		file.close ();

        if (found) {
        	cout << "Admin login successful!\n";
     		return true;
    	} else {
            cout << "Login failed! Incorrect admin credentials.\n";
    		return false;
    	}
    }

    void display() override {
    	cout << "Welcome, Admin " << username << "!\n";
    }

    void displayAllUsers () {
		cout << "Registered Users:\n";
    	ifstream file("users.txt");
    	string user, pass;
    	int count = 0;

       	while (file >> user >> pass) {
        	cout << count + 1 << ". " << user << endl;
    		count++;
    	}
		file.close ();

        if (count == 0) {
            cout << "No users registered yet.\n";
        }
    }

    void deleteUser () {
    	string userToDelete;
    		
		cout << "Enter username to delete: ";
    	cin >> userToDelete;

    	ifstream inFile ("users.txt");
    	ofstream tempFile ("temp.txt");
		string storedUser, storedPass;
    	bool found = false;

    	while (inFile >> storedUser >> storedPass) {
    		if (storedUser == userToDelete) {
            	found = true;
        		continue;
    		}
        	tempFile << storedUser << " " << storedPass << endl;
    	}
		inFile.close ();
    	tempFile.close ();

    	remove	("users.txt");
    	rename	("temp.txt", "users.txt");

    	if (found) {
        	cout << "User '" << userToDelete << "' deleted successfully.\n";
    	} else {
    		cout << "User not found.\n";
    	}
	}

    void changePassword() {
    	string currentUser, currentPass;
        	
		cout << "Enter current admin username: ";
    	cin >> currentUser;
    	cout << "Enter current admin password: ";
    	cin >> currentPass;

    	ifstream inFile("admins.txt");
    	ofstream tempFile("temp_admins.txt");
		string storedUser, storedPass;
    	bool found = false;

    	while (inFile >> storedUser >> storedPass) {
    		if (storedUser == currentUser && storedPass == currentPass) {
                found = true;
        		string newPass;
                		
				cout << "Enter new admin password: ";
            	cin >> newPass;
            	tempFile << storedUser << " " << newPass << endl;
            } else {
            	tempFile << storedUser << " " << storedPass << endl;
        	}
        }
		inFile.close ();
        tempFile.close ();

        remove ("admins.txt");
        rename ("temp_admins.txt", "admins.txt");

        if (found) {
            cout << "Admin password changed successfully!\n";
        } else {
            cout << "Incorrect credentials. Password not changed.\n";
        }
    }

	~Admin () {}
};


class User : public Person {
private:
	string username;
   	string password;

public:
   	User () {}

  	void setUsername (string u) { username = u; }
   	void setPassword (string p) { password = p; }

    string getUsername () { return username; }
	string getPassword () { return password; }

   	bool usernameExists (string& usernameToCheck) {
    	ifstream file ("users.txt");
    		if (!file) {
        		cout << "Error: Could not open file for reading.\n" << endl;
        		return false;
    		}
		string storedUser, storedPass;
    		
		while (file >> storedUser >> storedPass) {
        	if (storedUser == usernameToCheck) {
	    		cout << "Username already taken.\n";
            		return true;
        	}
    	}
    	return false;
    }

    void registerUser () override {
		do {
        	cout << "Enter new username: ";
        	cin >> username;
    	} while (usernameExists (username) != false);

        cout << "Enter new password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);
        file << username << " " << password << endl;
        file.close ();

        cout << "Registration successful!\n";
    }

    bool loginUser() override {
        string u, p;
        
		cout << "\nEnter username: ";
    	cin >> u;
		cout << "Enter password: ";
        cin >> p;

        ifstream file("users.txt");
        string storedUser, storedPass;
        bool found = false;

        while (file >> storedUser >> storedPass) {
        	if (storedUser == u && storedPass == p) {
                found = true;
				username = u;
                break;
            }
        }
        file.close ();

        if (found) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Login failed! Username or password is incorrect.\n";
            return false;
        }
    }

	void changePassword() {
    	string currentUser, currentPass;
    
		cout << "Enter current username: ";
    	cin >> currentUser;
    	cout << "Enter current password: ";
    	cin >> currentPass;

    	ifstream inFile("users.txt");
    	ofstream tempFile("temp.txt");
		string storedUser, storedPass;
    	bool found = false;

    	while (inFile >> storedUser >> storedPass) {
        	if (storedUser == currentUser && storedPass == currentPass) {
            	found = true;
            	string newPass;
            	cout << "Enter new password: ";
            	cin >> newPass;
        	    tempFile << storedUser << " " << newPass << endl;
        	} else {
            	tempFile << storedUser << " " << storedPass << endl;
        	}
    	}
	    inFile.close ();
	    tempFile.close ();

    	remove ("users.txt");
	    rename ("temp.txt", "users.txt");

    	if (found) {
        	cout << "Password changed successfully!\n";
    	} else {
        	cout << "Username or password incorrect. Password not changed.\n";
    	}
	}

    void display() override {
        cout << "Welcome, " << username << "!\n";
    }

	~User () {}
};

void showMainMenu () {
    cout << "\n----- MAIN MENU -----\n1. User Portal\n2. Admin Portal\n3. Exit\nEnter your choice: ";
}

void showAdminMenu () {
	Admin admin;
    
	if (admin.loginUser ()) {
        admin.display ();
		int choice;
        do {
			cout << "\n--- Admin Portal ---\n1. Display All Users\n2. Delete a User\n3. Change Admin Password\n4. Logout\nEnter your choice: ";
        	cin >> choice;

        	switch (choice) {
                case 1:
                	admin.displayAllUsers ();
                	break;
            	case 2:
                	admin.deleteUser ();
                	break;
            	case 3:
                	admin.changePassword ();
                	break;
            	case 4:
					cout << "Logging out of Admin Dashboard...\n";
                	break;
            	default:
                	cout << "Invalid choice. Try again.\n";
        	}
    	} while (choice != 4);
	}
}

void showUserMenu () {
 	User user;
    int choice;
    
	do {
        cout << "\n--- User Portal ---\n1. Register\n2. Login\n3. Change Password\n4. Back to Main Menu\nEnter your choice: ";
    	cin >> choice;
		switch (choice) {
            case 1:
                user.registerUser ();
            	break;
            case 2:
                if (user.loginUser ()) { user.display (); }
                break;
        	case 3:
                user.changePassword ();
        		break;
            case 4:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

void loginSystem () {
	int choice;

    do {
        showMainMenu();
    	cin >> choice;

        switch (choice) {
            case 1:
            	showUserMenu();
            	break;
        	case 2:
                showAdminMenu();
            	break;
        	case 3:
            	cout << "Exiting Program. Goodbye!\n";
            	break;
        	default:
            	cout << "Invalid option. Try again.\n";
    	}
	} while (choice != 3);
}
