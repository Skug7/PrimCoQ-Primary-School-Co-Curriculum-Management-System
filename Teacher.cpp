#include "Teacher.h"
#include <iostream>
#include <iomanip>
using namespace std;

// =============================================================
//  Teacher.cpp  —  Implementation of Teacher class
// =============================================================

Teacher::Teacher()
    : Person(), staffID(""), subject("") {}

Teacher::Teacher(string id, string name, int age, string staffID, string subject)
    : Person(id, name, age), staffID(staffID), subject(subject) {}

Teacher::~Teacher() {}

// ---------- Getters ----------
string Teacher::getStaffID() const { return staffID; }
string Teacher::getSubject() const { return subject;  }

// ---------- Setters ----------
void Teacher::setStaffID(string staffID) { this->staffID = staffID; }
void Teacher::setSubject(string subject) { this->subject = subject;  }

// ---------- Polymorphic display ----------
void Teacher::displayInfo() const {
    cout << left
         << setw(10) << getStaffID()
         << setw(22) << getName()
         << "Subject: " << subject
         << endl;
}
