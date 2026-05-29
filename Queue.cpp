#include "Queue.h"
#include <iostream>
#include <iomanip>
using namespace std;

Queue::Queue() : front(NULL), rear(NULL), count(0) {}

Queue::~Queue() {
    QueueNode* current = front;
    while (current != NULL) {
        QueueNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    front = NULL;
    rear  = NULL;
    count = 0;
}

Queue::Queue(const Queue& other) : front(NULL), rear(NULL), count(0) {
    QueueNode* current = other.front;
    while (current != NULL) {
        QueueNode* newNode = new QueueNode(current->studentID, current->studentName);
        if (rear == NULL) {
            front = newNode;
            rear  = newNode;
        } else {
            rear->next = newNode;
            rear       = newNode;
        }
        count++;
        current = current->next;
    }
}

Queue& Queue::operator=(const Queue& other) {
    if (this == &other) return *this;   

    QueueNode* current = front;
    while (current != NULL) {
        QueueNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    front = NULL;
    rear  = NULL;
    count = 0;

    QueueNode* src = other.front;
    while (src != NULL) {
        QueueNode* newNode = new QueueNode(src->studentID, src->studentName);
        if (rear == NULL) {
            front = newNode;
            rear  = newNode;
        } else {
            rear->next = newNode;
            rear       = newNode;
        }
        count++;
        src = src->next;
    }

    return *this;
}

void Queue::enqueue(const string& studentID, const string& studentName) {
    QueueNode* newNode = new QueueNode(studentID, studentName);

    if (isEmpty()) {
        front = newNode;
        rear  = newNode;
    } else {
        rear->next = newNode;
        rear       = newNode;
    }

    count++;
    cout << "  \"" << studentName << "\" added to waitlist. "
         << "Position: " << count << endl;
}

string Queue::dequeue() {
    if (isEmpty()) {
        cout << "  Waitlist is empty. Nothing to dequeue." << endl;
        return "";
    }

    QueueNode* toDelete  = front;
    string     removedID   = front->studentID;
    string     removedName = front->studentName;

    front = front->next;
    if (front == NULL)
        rear = NULL;  

    delete toDelete;
    count--;

    cout << "  \"" << removedName << "\" has been moved from waitlist to enrolled." << endl;
    return removedID;
}

string Queue::peekFront() const {
    if (isEmpty()) return "";
    return front->studentID;
}

void Queue::displayWaitlist() const {
    if (isEmpty()) {
        cout << "  No students on the waitlist." << endl;
        return;
    }

    cout << "  Waitlist (" << count << " student(s) waiting):" << endl;
    cout << "  " << string(40, '-') << endl;
    cout << "  " << left << setw(6) << "Pos" << setw(12) << "Student ID" << "Name" << endl;
    cout << "  " << string(40, '-') << endl;

    QueueNode* current  = front;
    int        position = 1;
    while (current != NULL) {
        cout << "  " << left
             << setw(6)  << position
             << setw(12) << current->studentID
             << current->studentName << endl;
        current = current->next;
        position++;
    }
}

bool Queue::isEmpty()  const { return front == NULL; }
int  Queue::getCount() const { return count;          }

