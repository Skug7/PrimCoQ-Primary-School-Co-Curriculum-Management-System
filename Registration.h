#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>
using namespace std;

// =============================================================
//  Registration.h  —  Records a student's enrolment in a club
//  Stored as nodes inside the Linked List
//  Status can be "Active" (enrolled) or "Waitlisted"
// =============================================================

class Registration {
private:
    string registrationID;   // Unique ID, e.g. "REG001"
    string studentID;        // Links to a Student
    string studentName;      // Stored for quick display (avoids searching)
    string clubID;           // Links to a Club
    string clubName;         // Stored for quick display
    string dateTime;         // e.g. "2026-05-07 14:30"
    string status;           // "Active" or "Waitlisted"

public:
    // ---------- Constructors ----------
    Registration();
    Registration(string regID, string studentID, string studentName,
                 string clubID, string clubName,
                 string dateTime, string status = "Active");

    // ---------- Destructor ----------
    ~Registration();

    // ---------- Getters ----------
    string getRegistrationID() const;
    string getStudentID()      const;
    string getStudentName()    const;
    string getClubID()         const;
    string getClubName()       const;
    string getDateTime()       const;
    string getStatus()         const;

    // ---------- Setters ----------
    void setStatus(string status);
    void setDateTime(string dateTime);

    // ---------- Display ----------
    void displayRow()  const;   // One-line row for the registration list
};

#endif
