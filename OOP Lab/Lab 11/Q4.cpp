#include <iostream>
#include <exception>
#include <string>

using namespace std;

class DatabaseException : public exception {
public:
    const char* what() const noexcept override {
        return "A database error occurred.";
    }
};

class ConnectionFailedException : public DatabaseException {
};

class QueryTimeoutException : public DatabaseException {
};

template <typename T>
class DatabaseConnector {
private:
    T dbName;

public:
    DatabaseConnector(T name) : dbName(name) {}

    void connect() {
        if (dbName == "invalid_db") {
            throw ConnectionFailedException();
        }
        if (dbName == "slow_db") {
            throw QueryTimeoutException();
        }
        cout << "Connected to " << dbName << endl;
    }
};

int main() {
    try {
        cout << "Attempting to connect to invalid_db..." << endl;
        DatabaseConnector<string> db1("invalid_db");
        db1.connect();
    }
    catch (const ConnectionFailedException& e) {
        cout << "Caught ConnectionFailedException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    try {
        cout << "Attempting to connect to slow_db..." << endl;
        DatabaseConnector<string> db2("slow_db");
        db2.connect();
    }
    catch (const DatabaseException& e) {
        cout << "Caught a general DatabaseException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    return 0;
}
