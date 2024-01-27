#include <iostream>
#include "prqueue.h"

using namespace std;


int main() {
    // prqueue<int> pq1, pq2;

    // pq1.enqueue(10, 1);
    // pq1.enqueue(20, 2);
    // pq1.enqueue(30, 3);

    // pq2 = pq1;


    // pq1.peek();

    // pq1.enqueue(40, 4);

    // cout << "Priority Queue 1: " << endl;
    // cout << pq1.toString() << endl;

    // cout << "Priority Queue 2: " << endl;
    // cout << pq2.toString() << endl;

    prqueue<int> pq;

    // pq.enqueue(10, 1);
    // pq.enqueue(20, 1);
    // pq.enqueue(30, 2);
    // pq.enqueue(40, 3);
    // pq.size();


    // pq.dequeue();
    // pq.dequeue();
    // pq.dequeue();
    // pq.dequeue();
    // pq.size();

    pq.enqueue(25, 2);
    pq.enqueue(15, 1);
    pq.enqueue(5, 1);
    pq.peek();

    pq.enqueue(20, 3);
    pq.enqueue(15, 2);
    pq.peek();

    pq.enqueue(60, 3);
    pq.peek();
    
    pq.enqueue(9, 1);
    pq.enqueue(50, 1);
    pq.enqueue(75, 2);

    int val;
    int priority;

    pq.begin();

    while (pq.next(val, priority)) {
        cout << "Priority: " << priority << ", Value: " << val << endl;
    }

    // pq1.clear();
    // pq2.clear();
    pq.clear();

    return 0;
}