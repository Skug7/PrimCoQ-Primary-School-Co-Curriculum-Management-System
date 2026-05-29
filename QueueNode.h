#ifndef QUEUENODE_H
#define QUEUENODE_H

#include <string>
using namespace std;

// =============================================================
//  QueueNode.h  —  A single node in the waitlist Queue
//  Stores the student ID and name of a waiting student
// =============================================================

struct QueueNode {
    string studentID;
    string studentName;
    QueueNode* next;

    QueueNode(string id, string name) 
        : studentID(id), studentName(name), next(NULL) {}
};

#endif
