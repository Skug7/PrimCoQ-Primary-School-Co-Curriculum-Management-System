#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>
using namespace std;

// =============================================================
//  Student.h  —  Inherits from Person
//  Adds: year level, registration tracking
// =============================================================

const int MAX_CLUBS_PER_STUDENT = 5;  // A student can join at most 5 clubs

class Student : public Person {
private:
    int    yearLevel;                              // Primary year 1–6
    string registeredClubIDs[MAX_CLUBS_PER_STUDENT]; // Clubs this student has joined
    int    clubCount;                              // How many clubs they are in

public:
    // ---------- Constructors ----------
    Student();
    Student(string id, string name, int age, int yearLevel);

    // ---------- Destructor ----------
    ~Student();

    // ---------- Getters ----------
    int    getYearLevel()  const;
    int    getClubCount()  const;
    string getClubID(int index) const;   // Returns club ID at given index

    // ---------- Setters ----------
    void setYearLevel(int yearLevel);

    // ---------- Club registration helpers ----------
    // Returns true if successfully added, false if already full
    bool addClub(string clubID);

    // Returns true if found and removed, false if not registered
    bool removeClub(string clubID);

    // Returns true if the student is already registered for this club
    bool isRegisteredFor(string clubID) const;

    // ---------- Polymorphic display (overrides Person::displayInfo) ----------
    void displayInfo() const override;
};

#endif
