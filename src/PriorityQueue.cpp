#include <iostream>
using namespace std;

class PriorityQueueNode {
public:
    int data;
    PriorityQueueNode* next;

    PriorityQueueNode(int value) {
        data = value;
        next = nullptr;
    }
};

class PriorityQueue {
private:
    PriorityQueueNode* head;

public:
    PriorityQueue() {
        head = nullptr;
    }

    ~PriorityQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Enqueue with priority (min-priority: smallest number is highest priority)
    void enqueue(int value) {
        PriorityQueueNode* newNode = new PriorityQueueNode(value);

        // Insert at the beginning if queue is empty or value is smaller than head
        if (head == nullptr || value < head->data) {
            newNode->next = head;
            head = newNode;
        } else {
            PriorityQueueNode* current = head;
            while (current->next != nullptr && current->next->data <= value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Remove element with highest priority (smallest value)
    void dequeue() {
        if (isEmpty()) {
            cout << "Priority Queue is empty.\n";
            return;
        }
        PriorityQueueNode* temp = head;
        head = head->next;
        delete temp;
    }

    int peek() const {
        if (isEmpty()) {
            cerr << "Priority Queue is empty.\n";
            return -1;
        }
        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void display() const {
        PriorityQueueNode* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};