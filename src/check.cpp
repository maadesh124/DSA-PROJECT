#include "Queue.cpp"
#include "PriorityQueue.cpp"

int main() {
    cout << "---- Queue Test ----\n";
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.display();  // Output: 1 -> 2 -> 3 -> NULL
    q.dequeue();
    q.display();  // Output: 2 -> 3 -> NULL

    cout << "\n---- Priority Queue Test (Min) ----\n";
    PriorityQueue pq;
    pq.enqueue(30);
    pq.enqueue(10);
    pq.enqueue(20);
    pq.enqueue(50);
    pq.display();  // Output: 10 -> 20 -> 30 -> 50 -> NULL
    pq.dequeue();
    pq.display();  // Output: 20 -> 30 -> 50 -> NULL

    return 0;
}
