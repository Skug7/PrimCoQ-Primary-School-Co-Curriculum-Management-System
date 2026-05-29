#ifndef QUEUE_H
#define QUEUE_H

#include "QueueNode.h"
#include <string>
using namespace std;

class Queue {
private:
    QueueNode* front;   
    QueueNode* rear;    
    int        count;   

public:
    Queue();
    ~Queue();

    Queue(const Queue& other);             
    Queue& operator=(const Queue& other);  

    void   enqueue(const string& studentID, const string& studentName);
    string dequeue();          
    string peekFront() const;  

    bool isEmpty() const;
    int  getCount() const;

    void displayWaitlist() const;
};

#endif
