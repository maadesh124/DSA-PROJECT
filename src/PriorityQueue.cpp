#include <iostream>

using namespace std;
struct PriorityQueueNode {
    int index;
    int dist;
    PriorityQueueNode* next;

    PriorityQueueNode(int i, int d) : index(i), dist(d), next(nullptr) {}
};

class MinPriorityQueue {
private:
    PriorityQueueNode* head;

public:
    MinPriorityQueue() : head(nullptr) {}

    bool isEmpty() {
        return head == nullptr;
    }

    void enqueue(int index, int dist) {
        PriorityQueueNode* newNode = new PriorityQueueNode(index, dist);

        // Insert at head if empty or smaller than current head
        if (!head || dist < head->dist) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Find correct position to insert
        PriorityQueueNode* curr = head;
        while (curr->next && curr->next->dist <= dist) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
    }

    int dequeue() {
        if (isEmpty()) return -1;

        int retIndex = head->index;
        PriorityQueueNode* temp = head;
        head = head->next;
        delete temp;
        return retIndex;
    }

    void printQueue() {
        PriorityQueueNode* curr = head;
        while (curr) {
            std::cout << "(" << curr->index << "," << curr->dist << ") ";
            curr = curr->next;
        }
        std::cout << "\n";
    }

    ~MinPriorityQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};
