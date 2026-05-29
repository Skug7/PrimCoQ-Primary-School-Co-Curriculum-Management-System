#include "ClubArray.h"
#include <iostream>
#include <iomanip>
using namespace std;

ClubArray::ClubArray() : count(0) {}

int ClubArray::findIndex(const string& clubID) const {
    for (int i = 0; i < count; i++) {
        if (clubs[i].getClubID() == clubID)
            return i;
    }
    return -1;
}

bool ClubArray::addClub(Club c) {
    if (isFull()) {
        cout << "  Club list is full. Cannot add more clubs." << endl;
        return false;
    }
    if (findIndex(c.getClubID()) != -1) {
        cout << "  Club ID \"" << c.getClubID() << "\" already exists." << endl;
        return false;
    }

    clubs[count] = c;
    count++;

    sortBy("id");

    cout << "  Club \"" << c.getName() << "\" added successfully." << endl;
    return true;
}

void ClubArray::displayAll() const {
    if (count == 0) {
        cout << "  No clubs in the system." << endl;
        return;
    }
    displayHeader();
    for (int i = 0; i < count; i++) {
        if (clubs[i].getIsActive())      //
            clubs[i].displayRow();
    }
    cout << string(72, '-') << endl;
}

bool ClubArray::updateClub(const string& clubID,
                            const string& newName,
                            const string& newCategory,
                            int           newCapacity,
                            const string& newClassroom,
                            const string& newTime,
                            const string& newTeacher) {
    int idx = findIndex(clubID);
    if (idx == -1) {
        cout << "  Club ID \"" << clubID << "\" not found." << endl;
        return false;
    }

    clubs[idx].setName(newName);
    clubs[idx].setCategory(newCategory);
    clubs[idx].setCapacity(newCapacity);   
    clubs[idx].setClassroom(newClassroom);
    clubs[idx].setMeetingTime(newTime);
    clubs[idx].setTeacherInCharge(newTeacher);

    cout << "  Club \"" << clubID << "\" updated successfully." << endl;
    return true;
}

bool ClubArray::cancelClub(const string& clubID) {
    int idx = findIndex(clubID);
    if (idx == -1) {
        cout << "  Club ID \"" << clubID << "\" not found." << endl;
        return false;
    }
    if (!clubs[idx].getIsActive()) {
        cout << "  Club \"" << clubID << "\" is already cancelled." << endl;
        return false;
    }

    clubs[idx].setIsActive(false);
    cout << "  Club \"" << clubID << "\" has been cancelled." << endl;
    return true;
}

string ClubArray::enrollStudent(const string& clubID,
                                 const string& studentID,
                                 const string& studentName) {
    int idx = findIndex(clubID);
    if (idx == -1)                 return "not_found";
    if (!clubs[idx].getIsActive()) return "cancelled";

    if (clubs[idx].isFull()) {
        waitlists[idx].enqueue(studentID, studentName);
        return "waitlisted";
    }

    clubs[idx].enrol(studentID);
    return "enrolled";
}

string ClubArray::cancelEnrolment(const string& clubID,
                                   const string& studentID,
                                   const string& studentName) {
    int idx = findIndex(clubID);
    if (idx == -1) {
        cout << "  Club ID \"" << clubID << "\" not found." << endl;
        return "not_found";
    }

    if (clubs[idx].getEnrolledCount() <= 0) {
        cout << "  [Error] No students enrolled in \"" << clubs[idx].getName()
             << "\". Cannot cancel." << endl;
        return "error";
    }

    clubs[idx].unenrol(studentID);
    cout << "  Student " << studentID << " (" << studentName << ") removed from \""
         << clubs[idx].getName() << "\"." << endl;

    if (!waitlists[idx].isEmpty()) {
        string nextID = waitlists[idx].dequeue();
        clubs[idx].enrol();
        cout << "  A slot opened — next waitlisted student (ID: " << nextID
             << ") has been enrolled." << endl;
    }

    return "cancelled";
}

void ClubArray::displayWaitlist(const string& clubID) {
    int idx = findIndex(clubID);
    if (idx == -1) {
        cout << "  Club ID \"" << clubID << "\" not found." << endl;
        return;
    }
    cout << "  Waitlist for: " << clubs[idx].getName() << endl;
    waitlists[idx].displayWaitlist();
}

Club* ClubArray::binarySearch(const string& clubID) {
    int low  = 0;
    int high = count - 1;

    while (low <= high) {
        int mid = (low + high) / 2;   

        if (clubs[mid].getClubID() == clubID) {
            return &clubs[mid];        
        }
        else if (clubs[mid].getClubID() < clubID) {
            low = mid + 1;            
        }
        else {
            high = mid - 1;            
        }
    }

    return NULL;  
}

void ClubArray::sortBy(const string& key) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            bool shouldSwap = false;

            if (key == "id") {
                if (clubs[j].getClubID() > clubs[j + 1].getClubID())
                    shouldSwap = true;
            }
            else if (key == "enrolled") {
                if (clubs[j].getEnrolledCount() < clubs[j + 1].getEnrolledCount())
                    shouldSwap = true;
            }

            if (shouldSwap) {
                // Swap clubs
                Club temp    = clubs[j];
                clubs[j]     = clubs[j + 1];
                clubs[j + 1] = temp;

                Queue tempQ      = waitlists[j];
                waitlists[j]     = waitlists[j + 1];
                waitlists[j + 1] = tempQ;
            }
        }
    }
}

void ClubArray::displayReport() {
    if (count == 0) {
        cout << "  No clubs to report." << endl;
        return;
    }

    cout << endl;
    cout << "  Sort report by:" << endl;
    cout << "  [1] Club ID (Default)" << endl;
    cout << "  [2] Total Students Enrolled" << endl;
    cout << "  Enter choice: ";

    int sortChoice;
    cin >> sortChoice;

    string sortKey   = "id";
    string sortLabel = "Club ID";
    if (sortChoice == 2) {
        sortKey   = "enrolled";
        sortLabel = "Total Students Enrolled";
    }

    sortBy(sortKey);

    cout << endl;
    cout << "  ================================================================" << endl;
    cout << "           CLUB POPULARITY & CAPACITY REPORT                      " << endl;
    cout << "           Sorted by: " << sortLabel                               << endl;
    cout << "  ================================================================" << endl;
    cout << "  " << left
         << setw(7)  << "Club ID"
         << setw(22) << "Club Name"
         << setw(16) << "Category"
         << setw(16) << "Total Enrolled"
         << setw(11) << "Status"
         << "Waitlist" << endl;
    cout << "  " << string(75, '-') << endl;

    for (int i = 0; i < count; i++) {
        string enrolled = to_string(clubs[i].getEnrolledCount())
                        + " / "
                        + to_string(clubs[i].getCapacity());

        cout << "  " << left
             << setw(7)  << clubs[i].getClubID()
             << setw(22) << clubs[i].getName()
             << setw(16) << clubs[i].getCategory()
             << setw(16) << enrolled
             << setw(11) << clubs[i].getStatusLabel()
             << waitlists[i].getCount()
             << endl;
    }
    cout << "  " << string(75, '-') << endl;

    sortBy("id");
}

int  ClubArray::getCount() const { return count;              }
bool ClubArray::isFull()   const { return count >= MAX_CLUBS; }

void ClubArray::displayHeader() const {
    cout << string(72, '-') << endl;
    cout << left
         << setw(8)  << "ID"
         << setw(22) << "Name"
         << setw(17) << "Category"
         << setw(12) << "Enrolled"
         << setw(12) << "Status"
         << "Classroom" << endl;
    cout << string(72, '-') << endl;
}
void ClubArray::displayStudentsInClub(const string& clubID) {
    int idx = findIndex(clubID);
    if (idx == -1) {
        cout << "  Club ID \"" << clubID << "\" not found." << endl;
        return;
    }
    clubs[idx].displayEnrolledStudents();
    // Also show waitlist if any
    if (!waitlists[idx].isEmpty()) {
        cout << endl;
        waitlists[idx].displayWaitlist();
    }
}
