#include "Club.h"
#include <iostream>
#include <iomanip>
using namespace std;

Club::Club()
    : clubID(""), name(""), category(""), capacity(0),
      enrolledCount(0), classroom(""), meetingTime(""),
      teacherInCharge(""), isActive(true) {
    for (int i = 0; i < 50; i++) enrolledStudentIDs[i] = "";
}

Club::Club(const string& id,   const string& nm,
           const string& cat,  int           cap,
           const string& room, const string& time,
           const string& teacher)
    : clubID(id), name(nm), category(cat),
      capacity(cap > 0 ? cap : 0),
      enrolledCount(0),
      classroom(room), meetingTime(time),
      teacherInCharge(teacher), isActive(true) {
    for (int i = 0; i < 50; i++) enrolledStudentIDs[i] = "";
}

string Club::getClubID()          const { return clubID;                  }
string Club::getName()            const { return name;                    }
string Club::getCategory()        const { return category;                }
int    Club::getCapacity()        const { return capacity;                }
int    Club::getEnrolledCount()   const { return enrolledCount;           }
int    Club::getAvailableSlots()  const { return capacity - enrolledCount;}
string Club::getClassroom()       const { return classroom;               }
string Club::getMeetingTime()     const { return meetingTime;             }
string Club::getTeacherInCharge() const { return teacherInCharge;         }
bool   Club::getIsActive()        const { return isActive;                }

bool Club::setClubID(const string& id) {
    if (id.empty()) {
        cout << "  [Error] Club ID cannot be empty.\n";
        return false;
    }
    clubID = id;
    return true;
}

bool Club::setName(const string& nm) {
    if (nm.empty()) {
        cout << "  [Error] Club name cannot be empty.\n";
        return false;
    }
    name = nm;
    return true;
}

bool Club::setCategory(const string& cat) {
    if (cat.empty()) {
        cout << "  [Error] Category cannot be empty.\n";
        return false;
    }
    category = cat;
    return true;
}

bool Club::setCapacity(int cap) {
    if (cap < 1) {
        cout << "  [Error] Capacity must be at least 1.\n";
        return false;
    }
    if (cap < enrolledCount) {
        cout << "  [Error] New capacity (" << cap << ") cannot be less than "
             << "current enrolment (" << enrolledCount << ").\n";
        return false;
    }
    capacity = cap;
    return true;
}

bool Club::setClassroom(const string& room) {
    if (room.empty()) {
        cout << "  [Error] Classroom cannot be empty.\n";
        return false;
    }
    classroom = room;
    return true;
}

bool Club::setMeetingTime(const string& time) {
    if (time.empty()) {
        cout << "  [Error] Meeting time cannot be empty.\n";
        return false;
    }
    meetingTime = time;
    return true;
}

bool Club::setTeacherInCharge(const string& teacher) {
    if (teacher.empty()) {
        cout << "  [Error] Teacher-in-charge cannot be empty.\n";
        return false;
    }
    teacherInCharge = teacher;
    return true;
}

void Club::setIsActive(bool active) {
    isActive = active;
}

bool Club::enrol(const string& studentID) {
    if (!isActive) {
        cout << "  [Error] \"" << name << "\" is cancelled.\n";
        return false;
    }
    if (isFull()) {
        cout << "  [Error] \"" << name << "\" is full.\n";
        return false;
    }
    if (!studentID.empty())
        enrolledStudentIDs[enrolledCount] = studentID;
    enrolledCount++;
    return true;
}

bool Club::unenrol(const string& studentID) {
    if (enrolledCount <= 0) {
        cout << "  [Error] No enrolled students in \"" << name << "\".\n";
        return false;
    }
    // Remove studentID from the list if provided
    if (!studentID.empty()) {
        for (int i = 0; i < enrolledCount; i++) {
            if (enrolledStudentIDs[i] == studentID) {
                // Shift left
                for (int j = i; j < enrolledCount - 1; j++)
                    enrolledStudentIDs[j] = enrolledStudentIDs[j + 1];
                enrolledStudentIDs[enrolledCount - 1] = "";
                break;
            }
        }
    }
    enrolledCount--;
    return true;
}

bool Club::isFull()      const { return enrolledCount >= capacity; }
bool Club::isAvailable() const { return !isFull() && isActive;     }

string Club::getStatusLabel() const {
    if (!isActive) return "Cancelled";
    if (isFull())  return "Full";
    return "Available";
}

void Club::displayEnrolledStudents() const {
    cout << "  Students enrolled in \"" << name << "\" (" 
         << enrolledCount << " / " << capacity << "):" << endl;
    if (enrolledCount == 0) {
        cout << "  No students enrolled yet." << endl;
        return;
    }
    cout << "  " << string(30, '-') << endl;
    for (int i = 0; i < enrolledCount; i++) {
        cout << "  " << (i + 1) << ". " << enrolledStudentIDs[i] << endl;
    }
}
bool Club::operator==(const Club& other) const { return clubID == other.clubID; }
bool Club::operator< (const Club& other) const { return clubID <  other.clubID; }
bool Club::operator> (const Club& other) const { return clubID >  other.clubID; }

bool Club::hasMoreEnrolledThan(const Club& other) const {
    return enrolledCount > other.enrolledCount;
}

void Club::displayRow() const {
    string enrolStr = to_string(enrolledCount) + " / " + to_string(capacity);
    cout << left
         << setw(8)  << clubID
         << setw(22) << name
         << setw(17) << category
         << setw(12) << enrolStr
         << setw(12) << getStatusLabel()
         << classroom
         << endl;
}

void Club::displayFull() const {
    cout << "========================================" << endl;
    cout << " Club ID     : " << clubID       << endl;
    cout << " Name        : " << name         << endl;
    cout << " Category    : " << category     << endl;
    cout << " Enrolment   : " << enrolledCount << " / " << capacity
         << "  (" << getAvailableSlots() << " slot(s) left)" << endl;
    cout << " Status      : " << getStatusLabel() << endl;
    cout << " Classroom   : " << classroom    << endl;
    cout << " Meeting     : " << meetingTime  << endl;
    cout << " Teacher     : " << teacherInCharge << endl;
    cout << "========================================" << endl;
}
