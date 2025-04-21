#include "PriorityQueue.cpp"

using namespace std;
int main() {
    MinPriorityQueue pq;

    // Enqueue some elements
    pq.enqueue(2, 8);
    pq.enqueue(5, 3);
    pq.enqueue(1, 10);
    pq.enqueue(4, 7);
    pq.enqueue(0, 2);

    pq.printQueue();  // Expected order by dist: (0,2) (5,3) (4,7) (2,8) (1,10)

    // Dequeue elements one by one
    cout << "\nDequeuing all elements:\n";
    while (!pq.isEmpty()) {
        int minIndex = pq.dequeue();
        cout << "Dequeued index: " << minIndex << endl;
        pq.printQueue();
    }

    return 0;
}
