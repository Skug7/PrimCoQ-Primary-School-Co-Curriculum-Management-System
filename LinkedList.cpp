#include "LinkedList.h"
#include <iostream>
#include <iomanip>
using namespace std;

LinkedList::LinkedList() : head(NULL), size(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next; 
        delete current;                  
        current = nextNode;              
    }
}


void LinkedList::addStudent(Student s) {
    Node* newNode = new Node(s);  
    
    if (head == NULL) {
        head = newNode;
    }

    else {
        Node* current = head;
        while (current->next != NULL) { 
            current = current->next;
        }
        current->next = newNode; 
    }

    size++;
    cout << "Student \"" << s.getName() << "\" added successfully." << endl;
}

void LinkedList::displayAll() const {
    if (isEmpty()) {
        cout << "  No students in the system." << endl;
        return;
    }

    displayHeader();

    Node* current = head;          
    while (current != NULL) {     
        current->data.displayInfo();   
        current = current->next;  
    }

    cout << "  Total students: " << size << endl;
}


Node* LinkedList::linearSearch(string id) const {
    Node* current = head;

    while (current != NULL) {
        if (current->data.getId() == id) {
            return current;   
        }
        current = current->next; 
    }

    return NULL;  
}

Node* LinkedList::linearSearchByName(string name) const {
    Node* current = head;

    while (current != NULL) {
        if (current->data.getName() == name) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

bool LinkedList::updateStudent(string id, string newName, int newAge, int newYear) {
    Node* found = linearSearch(id);  // 先找

    if (found == NULL) {
        cout << "  Student ID \"" << id << "\" not found." << endl;
        return false;
    }

    found->data.setName(newName);
    found->data.setAge(newAge);
    found->data.setYearLevel(newYear);

    cout << "  Student \"" << id << "\" updated successfully." << endl;
    return true;
}

bool LinkedList::deleteStudent(string id) {
    if (isEmpty()) {
        cout << "  List is empty." << endl;
        return false;
    }

    if (head->data.getId() == id) {
        Node* toDelete = head;      
        head = head->next;          
        delete toDelete;          
        size--;
        cout << "  Student \"" << id << "\" deleted." << endl;
        return true;
    }
    
    Node* prev    = head;
    Node* current = head->next;

    while (current != NULL) {
        if (current->data.getId() == id) {
            prev->next = current->next;  
            delete current;              
            size--;
            cout << "  Student \"" << id << "\" deleted." << endl;
            return true;
        }
        prev    = current;
        current = current->next;
    }

    cout << "  Student ID \"" << id << "\" not found." << endl;
    return false;
}


// ─────────────────────────────────────────────────────────────
//  Helper functions
// ─────────────────────────────────────────────────────────────
int  LinkedList::getSize()  const { return size;          }
bool LinkedList::isEmpty()  const { return head == NULL;  }

void LinkedList::displayHeader() const {
    cout << string(70, '-') << endl;
    cout << left
         << setw(10) << "ID"
         << setw(22) << "Name"
         << setw(8)  << "Year"
         << setw(6)  << "Age"
         << "Clubs Joined"
         << endl;
    cout << string(70, '-') << endl;
}
