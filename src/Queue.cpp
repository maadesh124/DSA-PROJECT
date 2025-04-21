#include <iostream>
using namespace std;

class QueueNode {
public:
    int data;
    QueueNode* next;

    QueueNode(int value) {
        data = value;
        next = nullptr;
    }
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;  // Track the number of elements

public:
    Queue() {
        front = rear = nullptr;
        count = 0;
    }

    ~Queue() {
        while (!isEmpty()) {
            deque();
        }
    }

    void enqueue(int value) {
        QueueNode* newNode = new QueueNode(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;  // Increment size
    }

    void deque() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        QueueNode* temp = front;
        front = front->next;
        delete temp;
        count--;  // Decrement size

        if (front == nullptr)
            rear = nullptr;
    }

    int peek() const {
        if (isEmpty()) {
            cerr << "Queue is empty.\n";
            return -1;
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int size() const {
        return count;
    }

    void display() const {
        QueueNode* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};
