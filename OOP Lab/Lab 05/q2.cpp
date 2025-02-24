#include <iostream>
using namespace std;

class Student {
private:
    int id;
    string name;
    int* scores;
    int numScores;

public:
    Student(int _id, string _name, int _numScores, int* _scores) {
        id = _id;
        name = _name;
        numScores = _numScores;
        scores = new int[numScores];
        for (int i = 0; i < numScores; i++) {
            scores[i] = _scores[i];
        }
    }

    Student(const Student &other) {
        id = other.id;
        name = other.name;
        numScores = other.numScores;
        scores = new int[numScores];
        for (int i = 0; i < numScores; i++) {
            scores[i] = other.scores[i];
        }
    }

    void display() const {
        cout << "Student ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Scores: ";
        for (int i = 0; i < numScores; i++) {
            cout << scores[i] << " ";
        }
        cout << endl;
    }

    ~Student() {
        delete[] scores;
    }
};

int main() {
    int scores1[] = {85, 90, 78};
    Student student1(640, "Huzaif", 3, scores1);
    cout << "Original Student Record:" << endl;
    student1.display();

    Student student2 = student1;
    cout << "Copied Student Record:" << endl;
    student2.display();
    
    return 0;
}
