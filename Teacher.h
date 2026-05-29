#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"
#include <string>
using namespace std;

// =============================================================
//  Teacher.h  —  Inherits from Person
//  Represents a teacher who is assigned as club in-charge
// =============================================================

class Teacher : public Person {
private:
    string staffID;
    string subject;       // e.g. "Mathematics", "Physical Education"

public:
    // ---------- Constructors ----------
    Teacher();
    Teacher(string id, string name, int age, string staffID, string subject);

    // ---------- Destructor ----------
    ~Teacher();

    // ---------- Getters ----------
    string getStaffID()  const;
    string getSubject()  const;

    // ---------- Setters ----------
    void setStaffID(string staffID);
    void setSubject(string subject);

    // ---------- Polymorphic display (overrides Person::displayInfo) ----------
    void displayInfo() const override;
};

#endif
