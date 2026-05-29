#include "Registration.h"
#include <iostream>
#include <iomanip>
using namespace std;

// =============================================================
//  Registration.cpp  —  Implementation of Registration class
// =============================================================

Registration::Registration()
    : registrationID(""), studentID(""), studentName(""),
      clubID(""), clubName(""), dateTime(""), status("Active") {}

Registration::Registration(string regID, string studentID, string studentName,
                           string clubID, string clubName,
                           string dateTime, string status)
    : registrationID(regID), studentID(studentID), studentName(studentName),
      clubID(clubID), clubName(clubName), dateTime(dateTime), status(status) {}

Registration::~Registration() {}

// ---------- Getters ----------
string Registration::getRegistrationID() const { return registrationID; }
string Registration::getStudentID()      const { return studentID;      }
string Registration::getStudentName()    const { return studentName;    }
string Registration::getClubID()         const { return clubID;         }
string Registration::getClubName()       const { return clubName;       }
string Registration::getDateTime()       const { return dateTime;       }
string Registration::getStatus()         const { return status;         }

// ---------- Setters ----------
void Registration::setStatus(string status)     { this->status   = status;   }
void Registration::setDateTime(string dateTime) { this->dateTime = dateTime; }

// ---------- Display ----------
void Registration::displayRow() const {
    cout << left
         << setw(10) << registrationID
         << setw(12) << studentID
         << setw(20) << studentName
         << setw(8)  << clubID
         << setw(20) << clubName
         << setw(12) << status
         << dateTime
         << endl;
}
