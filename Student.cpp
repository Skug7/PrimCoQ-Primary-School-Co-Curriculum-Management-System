#include "Student.h"
#include <iostream>
#include <iomanip>
using namespace std;

// =============================================================
//  Student.cpp  —  Implementation of Student class
// =============================================================

// ---------- Constructors ----------
Student::Student()
    : Person(), yearLevel(1), clubCount(0) {
    for (int i = 0; i < MAX_CLUBS_PER_STUDENT; i++)
        registeredClubIDs[i] = "";
}

Student::Student(string id, string name, int age, int yearLevel)
    : Person(id, name, age), yearLevel(yearLevel), clubCount(0) {
    for (int i = 0; i < MAX_CLUBS_PER_STUDENT; i++)
        registeredClubIDs[i] = "";
}

// ---------- Destructor ----------
Student::~Student() {}

// ---------- Getters ----------
int    Student::getYearLevel()        const { return yearLevel;  }
int    Student::getClubCount()        const { return clubCount;  }
string Student::getClubID(int index)  const {
    if (index >= 0 && index < clubCount)
        return registeredClubIDs[index];
    return "";
}

// ---------- Setters ----------
void Student::setYearLevel(int yearLevel) { this->yearLevel = yearLevel; }

// ---------- Club registration helpers ----------
bool Student::addClub(string clubID) {
    // Prevent joining the same club twice
    if (isRegisteredFor(clubID)) return false;

    // Prevent exceeding the per-student club limit
    if (clubCount >= MAX_CLUBS_PER_STUDENT) return false;

    registeredClubIDs[clubCount] = clubID;
    clubCount++;
    return true;
}

bool Student::removeClub(string clubID) {
    for (int i = 0; i < clubCount; i++) {
        if (registeredClubIDs[i] == clubID) {
            // Shift remaining entries left to fill the gap
            for (int j = i; j < clubCount - 1; j++)
                registeredClubIDs[j] = registeredClubIDs[j + 1];
            registeredClubIDs[clubCount - 1] = "";
            clubCount--;
            return true;
        }
    }
    return false;  // Not found
}

bool Student::isRegisteredFor(string clubID) const {
    for (int i = 0; i < clubCount; i++)
        if (registeredClubIDs[i] == clubID) return true;
    return false;
}

// ---------- Polymorphic display ----------
void Student::displayInfo() const {
    cout << left
         << setw(10) << getId()
         << setw(22) << getName()
         << "Year " << getYearLevel()
         << "   Age: " << getAge()
         << "   Clubs joined: " << clubCount
         << endl;
}
