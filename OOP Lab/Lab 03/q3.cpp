#include <iostream>
using namespace std;

class Library {
private:
    string bookList[50];       
    string borrowedBooks[50];  
    string borrowers[50];       
    int totalBooks;
    int borrowedCount;

public:
    Library() : totalBooks(0), borrowedCount(0) {
        cout << "Library system initialized.\n";
    }

    void addBook(string bookName) {
        if (totalBooks < 50) {
            bookList[totalBooks++] = bookName;
            cout << "Book '" << bookName << "' added to the library.\n";
        } else {
            cout << "Library is full! Cannot add more books.\n";
        }
    }

    void lendBook(string bookName, string studentName) {
        for (int i = 0; i < totalBooks; i++) {
            if (bookList[i] == bookName) {
                // Move book to borrowed list
                borrowedBooks[borrowedCount] = bookName;
                borrowers[borrowedCount++] = studentName;
                for (int j = i; j < totalBooks - 1; j++) {
                    bookList[j] = bookList[j + 1];
                }
                totalBooks--;
                cout << "Book '" << bookName << "' borrowed by " << studentName << ".\n";
                return;
            }
        }
        cout << "Book '" << bookName << "' is not available.\n";
    }

    void returnBook(string bookName) {
        for (int i = 0; i < borrowedCount; i++) {
            if (borrowedBooks[i] == bookName) {
                bookList[totalBooks++] = borrowedBooks[i];
                cout << "Book '" << borrowedBooks[i] << "' 
                for (int j = i; j < borrowedCount - 1; j++) {
                    borrowedBooks[j] = borrowedBooks[j + 1];
                    borrowers[j] = borrowers[j + 1];
                }
                borrowedCount--;
                return;
            }
        }
        cout << "Book '" << bookName << "' was not borrowed.\n";
    }

    void displayBooks() {
        cout << "\nAvailable Books:\n";
        if (totalBooks == 0) {
            cout << "No books available in the library.\n";
        } else {
            for (int i = 0; i < totalBooks; i++) {
                cout << i + 1 << ". " << bookList[i] << endl;
            }
        }
    }

    void displayBorrowedBooks() {
        cout << "\nBorrowed Books:\n";
        if (borrowedCount == 0) {
            cout << "No books are currently borrowed.\n";
        } else {
            for (int i = 0; i < borrowedCount; i++) {
                cout << i + 1 << ". " << borrowedBooks[i] << " (Borrowed by: " << borrowers[i] << ")\n";
            }
        }
    }
};

int main() {
    Library library;
    
    library.addBook("The Art of War");
    library.addBook("Murder of History");
    library.addBook("Beyound Good and Evil");
    library.addBook("The Republic");

    library.displayBooks();

    library.lendBook("The Art of War", "Huzaif");
    library.lendBook("Murder of History", "Kazim");

    library.displayBooks();
    library.displayBorrowedBooks();

    library.returnBook("The Art of War");

    library.displayBooks();
    library.displayBorrowedBooks();

    return 0;
}
