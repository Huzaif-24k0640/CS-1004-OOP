#include <iostream>
#include <exception>

using namespace std;

class QueueOverflowException : public exception {
};

class QueueUnderflowException : public exception {
};

template <typename T, int SIZE>
class Queue {
private:
    T data[SIZE];
    int frontIndex;
    int rearIndex;
    int count;

public:
    Queue() : frontIndex(0), rearIndex(-1), count(0) {}

    void enqueue(T value) {
        if (count == SIZE) {
            throw QueueOverflowException();
        }
        rearIndex = (rearIndex + 1) % SIZE;
        data[rearIndex] = value;
        count++;
    }

    T dequeue() {
        if (count == 0) {
            throw QueueUnderflowException();
        }
        T value = data[frontIndex];
        frontIndex = (frontIndex + 1) % SIZE;
        count--;
        return value;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == SIZE;
    }

    int size() const {
        return count;
    }
};

int main() {
    Queue<int, 3> q;

    try {
        cout << "Attempting to enqueue to a full queue..." << endl;
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);
        q.enqueue(40);
    }
    catch (const QueueOverflowException& e) {
        cout << "Caught QueueOverflowException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    try {
        Queue<int, 2> emptyQueue;
        cout << "Attempting to dequeue from an empty queue..." << endl;
        emptyQueue.dequeue();
    }
    catch (const QueueUnderflowException& e) {
        cout << "Caught QueueUnderflowException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    return 0;
}
