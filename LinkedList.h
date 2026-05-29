#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "Student.h"
#include <string>
using namespace std;

// =============================================================
//  LinkedList.h  —  store all Student 
//
//  head
//   |
//   v
//  [Ali|next] --> [Siti|next] --> [Raju|next] --> NULL
// =============================================================

class LinkedList {
private:
    Node* head;   // if linked list empty，head = NULL
    int   size;   // record have how many student

public:
    // ---------- Constructor & Destructor ----------
    LinkedList();
    ~LinkedList();  

    // ---------- CRUD Operations ----------
    void addStudent(Student s);             
    void displayAll() const;              
    bool updateStudent(string id,
                       string newName,
                       int newAge,
                       int newYear);        
    bool deleteStudent(string id);          

    // ---------- Search ----------
    Node* linearSearch(string id) const;     // Linear Search by student ID
    Node* linearSearchByName(string name) const; // Linear Search by name

    // ---------- Helper ----------
    int  getSize()    const;
    bool isEmpty()    const;
    void displayHeader() const;  
};

#endif
