/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 01
 */

/*
* Create a program to manage a dynamic array of structures representing books in a library. Each book has a title, author, and year. The program should: 
* 1. Allow the user to input the number of books. 
* 2. Dynamically allocate memory for the books. 
* 3. Populate the array with user input. 
* 4. Display all books published after a specific year. 
* 5. Deallocate memory after use. 
*/

#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
};


void inputBooks(Book* books, int numBooks) {
    for (int i = 0; i < numBooks; i++) {
        cout << "Enter details for book " << i + 1 << ":\n";
        cout << "Title(use '_'(underscore) instead of ' '(whitespace)): ";
        cin >> books[i].title;
        cout << "Author(use '_'(underscore) instead of ' '(whitespace)): ";
        cin >> books[i].author;
        cout << "Year: ";
        cin >> books[i].year;
    }
}


void displayBooksAfterYear(Book* books, int numBooks, int year) {
    cout << "\nBooks published after " << year << ":\n";
    bool found = false;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].year > year) {
            cout << "Title: " << books[i].title << ", Author: " << books[i].author << ", Year: " << books[i].year << "\n";
            found = true;
        }
    }
    if (found == false) {
        cout << "No books found.\n";
    }
}

int main() {
    int numBooks;

    // 1. Array size
    cout << "Enter the number of books: ";
    cin >> numBooks;

    // 2. Allocation
    Book* books = new Book[numBooks];

    // 3. Input
    inputBooks(books, numBooks);

    // 4. Condition
    int searchYear;
    cout << "\nEnter a year to list books published after it: ";
    cin >> searchYear;
    displayBooksAfterYear(books, numBooks, searchYear);

    // 5. Deallocation
    delete[] books;

    return 0;
}
