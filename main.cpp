// =============================================================
//  main.cpp  —  PrimCoQ: Primary School Co-Curriculum
//               Management System
//
//  Entry point of the program. Handles all menus and user
//  interaction. Calls functions from ClubArray, LinkedList,
//  and the Registration history array.
//
//  Data Structures used:
//    - ClubArray          : Array-based list for Club records
//    - LinkedList         : Linked list for Student records
//    - Queue (in ClubArray): FIFO waitlist per club slot
//    - regHistory[]       : Array-based Registration history
//
//  Algorithms used:
//    - Linear Search : Search student by ID or name (linked list)
//    - Binary Search : Search club by ID (sorted array)
//    - Bubble Sort   : Sort clubs in the Popularity Report
// =============================================================

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Club.h"
#include "Registration.h"
#include "Node.h"
#include "LinkedList.h"
#include "QueueNode.h"
#include "Queue.h"
#include "ClubArray.h"
#include "Auth.h"

// =============================================================
//  ANSI Color Codes
// =============================================================
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define WHITE   "\033[97m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

// =============================================================
//  Global Data Structures
// =============================================================
ClubArray  clubList;
LinkedList studentList;
Auth       auth;

const int    MAX_REG   = 200;
Registration regHistory[MAX_REG];
int          regCount  = 0;
int          regCounter = 0;

// =============================================================
//  generateRegID()
// =============================================================
string generateRegID() {
    regCounter++;
    string id = "REG";
    if      (regCounter < 10)  id += "00" + to_string(regCounter);
    else if (regCounter < 100) id += "0"  + to_string(regCounter);
    else                       id += to_string(regCounter);
    return id;
}

// =============================================================
//  addRegistration()
// =============================================================
void addRegistration(const string& studentID,   const string& studentName,
                     const string& clubID,       const string& clubName,
                     const string& status) {
    if (regCount >= MAX_REG) {
        cout << RED << "  [Warning] Registration history is full." << RESET << endl;
        return;
    }
    regHistory[regCount] = Registration(
        generateRegID(),
        studentID, studentName,
        clubID, clubName,
        "2026-05-18",
        status
    );
    regCount++;
}

// =============================================================
//  displayRegistrationHistory()
// =============================================================
void displayRegistrationHistory() {
    if (regCount == 0) {
        cout << YELLOW << "  No registration records found." << RESET << endl;
        return;
    }
    cout << string(87, '-') << endl;
    cout << "  " << left
         << setw(8)  << "Reg ID"
         << setw(10) << "Stu ID"
         << setw(20) << "Student Name"
         << setw(8)  << "Club"
         << setw(22) << "Club Name"
         << setw(12) << "Status"
         << "Date" << endl;
    cout << string(87, '-') << endl;

    for (int i = 0; i < regCount; i++) {
        cout << "  ";
        regHistory[i].displayRow();
    }
    cout << string(87, '-') << endl;
    cout << GREEN << "  Total records: " << regCount << RESET << endl;
}

// =============================================================
//  Input helpers
// =============================================================
string inputString(const string& prompt) {
    string val;
    while (true) {
        cout << CYAN << prompt << RESET;
        getline(cin, val);
        if (!val.empty()) return val;
        cout << RED << "  [Error] Input cannot be empty. Try again." << RESET << endl;
    }
}

int inputInt(const string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << CYAN << prompt << RESET;
        if (cin >> val && val >= minVal && val <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "  [Error] Please enter a number between "
             << minVal << " and " << maxVal << "." << RESET << endl;
    }
}

// Ask "Are you sure? (y/n)" — returns true if confirmed
bool confirmAction(const string& msg) {
    cout << YELLOW << "  [Confirm] " << msg << " (y/n): " << RESET;
    string ans;
    getline(cin, ans);
    return (ans == "y" || ans == "Y");
}

// Section divider
void divider() {
    cout << endl ;
}

// Section title
void sectionTitle(const string& title) {
    cout << BOLD << WHITE << "  " << title << RESET << endl;
}

// =============================================================
//  loadPresetData()
// =============================================================
void loadPresetData() {
    streambuf* originalBuf = cout.rdbuf(NULL);

    clubList.addClub(Club("C-101", "Football Team",  CAT_SPORTS,   10, "Field A",     "Mon 2:00PM", "T-001"));
    clubList.addClub(Club("C-102", "Robotics Club",  CAT_ACADEMIC,  5, "Lab 2",       "Tue 3:00PM", "T-002"));
    clubList.addClub(Club("C-103", "Scouts",         CAT_UNIFORM,   8, "Hall B",      "Wed 2:30PM", "T-003"));
    clubList.addClub(Club("C-104", "Badminton Club", CAT_SPORTS,    6, "Sports Hall", "Thu 2:00PM", "T-001"));
    clubList.addClub(Club("C-105", "Art & Craft",    CAT_ARTS,      4, "Room 7",      "Fri 1:00PM", "T-004"));

    studentList.addStudent(Student("S-001", "Ahmad Farid",   11, 5));
    studentList.addStudent(Student("S-002", "Siti Aisyah",   10, 4));
    studentList.addStudent(Student("S-003", "Rajendran",     12, 6));
    studentList.addStudent(Student("S-004", "Mei Ling",      11, 5));
    studentList.addStudent(Student("S-005", "Haziq Syafiq",  10, 4));
    studentList.addStudent(Student("S-006", "Priya Devi",    12, 6));
    studentList.addStudent(Student("S-007", "Nurul Ain",     11, 5));
    studentList.addStudent(Student("S-008", "Darren Lim",    10, 4));
    studentList.addStudent(Student("S-009", "Kavitha",       12, 6));
    studentList.addStudent(Student("S-010", "Izzatul Husna", 11, 5));

    // C-101 Football (cap=10)
    clubList.enrollStudent("C-101", "S-001", "Ahmad Farid");
    clubList.enrollStudent("C-101", "S-002", "Siti Aisyah");
    clubList.enrollStudent("C-101", "S-003", "Rajendran");
    clubList.enrollStudent("C-101", "S-004", "Mei Ling");
    clubList.enrollStudent("C-101", "S-005", "Haziq Syafiq");
    clubList.enrollStudent("C-101", "S-006", "Priya Devi");
    clubList.enrollStudent("C-101", "S-007", "Nurul Ain");
    clubList.enrollStudent("C-101", "S-008", "Darren Lim");
    clubList.enrollStudent("C-101", "S-009", "Kavitha");
    clubList.enrollStudent("C-101", "S-010", "Izzatul Husna");
    clubList.enrollStudent("C-101", "S-002", "Siti Aisyah");   // waitlist
    clubList.enrollStudent("C-101", "S-004", "Mei Ling");      // waitlist

    // C-102 Robotics (cap=5)
    clubList.enrollStudent("C-102", "S-001", "Ahmad Farid");
    clubList.enrollStudent("C-102", "S-003", "Rajendran");
    clubList.enrollStudent("C-102", "S-005", "Haziq Syafiq");
    clubList.enrollStudent("C-102", "S-007", "Nurul Ain");
    clubList.enrollStudent("C-102", "S-009", "Kavitha");
    clubList.enrollStudent("C-102", "S-010", "Izzatul Husna"); // waitlist

    // C-103 Scouts (cap=8)
    clubList.enrollStudent("C-103", "S-001", "Ahmad Farid");
    clubList.enrollStudent("C-103", "S-002", "Siti Aisyah");
    clubList.enrollStudent("C-103", "S-004", "Mei Ling");
    clubList.enrollStudent("C-103", "S-006", "Priya Devi");
    clubList.enrollStudent("C-103", "S-008", "Darren Lim");
    clubList.enrollStudent("C-103", "S-010", "Izzatul Husna");

    // C-104 Badminton (cap=6)
    clubList.enrollStudent("C-104", "S-002", "Siti Aisyah");
    clubList.enrollStudent("C-104", "S-003", "Rajendran");
    clubList.enrollStudent("C-104", "S-005", "Haziq Syafiq");
    clubList.enrollStudent("C-104", "S-009", "Kavitha");

    // C-105 Art & Craft (cap=4)
    clubList.enrollStudent("C-105", "S-006", "Priya Devi");

    // 在 loadPresetData() 里，enrolment 之后加这段
    // C-101
    studentList.linearSearch("S-001")->data.addClub("C-101");
    studentList.linearSearch("S-002")->data.addClub("C-101");
    studentList.linearSearch("S-003")->data.addClub("C-101");
    studentList.linearSearch("S-004")->data.addClub("C-101");
    studentList.linearSearch("S-005")->data.addClub("C-101");
    studentList.linearSearch("S-006")->data.addClub("C-101");
    studentList.linearSearch("S-007")->data.addClub("C-101");
    studentList.linearSearch("S-008")->data.addClub("C-101");
    studentList.linearSearch("S-009")->data.addClub("C-101");
    studentList.linearSearch("S-010")->data.addClub("C-101");
    // C-102
    studentList.linearSearch("S-001")->data.addClub("C-102");
    studentList.linearSearch("S-003")->data.addClub("C-102");
    studentList.linearSearch("S-005")->data.addClub("C-102");
    studentList.linearSearch("S-007")->data.addClub("C-102");
    studentList.linearSearch("S-009")->data.addClub("C-102");
    // C-103
    studentList.linearSearch("S-001")->data.addClub("C-103");
    studentList.linearSearch("S-002")->data.addClub("C-103");
    studentList.linearSearch("S-004")->data.addClub("C-103");
    studentList.linearSearch("S-006")->data.addClub("C-103");
    studentList.linearSearch("S-008")->data.addClub("C-103");
    studentList.linearSearch("S-010")->data.addClub("C-103");
    // C-104
    studentList.linearSearch("S-002")->data.addClub("C-104");
    studentList.linearSearch("S-003")->data.addClub("C-104");
    studentList.linearSearch("S-005")->data.addClub("C-104");
    studentList.linearSearch("S-009")->data.addClub("C-104");
    // C-105
    studentList.linearSearch("S-006")->data.addClub("C-105");

    cout.rdbuf(originalBuf);

    // Registration history
    addRegistration("S-001","Ahmad Farid",  "C-101","Football Team","Active");
    addRegistration("S-002","Siti Aisyah",  "C-101","Football Team","Active");
    addRegistration("S-003","Rajendran",    "C-101","Football Team","Active");
    addRegistration("S-004","Mei Ling",     "C-101","Football Team","Active");
    addRegistration("S-005","Haziq Syafiq", "C-101","Football Team","Active");
    addRegistration("S-006","Priya Devi",   "C-101","Football Team","Active");
    addRegistration("S-007","Nurul Ain",    "C-101","Football Team","Active");
    addRegistration("S-008","Darren Lim",   "C-101","Football Team","Active");
    addRegistration("S-009","Kavitha",      "C-101","Football Team","Active");
    addRegistration("S-010","Izzatul Husna","C-101","Football Team","Active");
    addRegistration("S-002","Siti Aisyah",  "C-101","Football Team","Waitlisted");
    addRegistration("S-004","Mei Ling",     "C-101","Football Team","Waitlisted");
    addRegistration("S-001","Ahmad Farid",  "C-102","Robotics Club","Active");
    addRegistration("S-003","Rajendran",    "C-102","Robotics Club","Active");
    addRegistration("S-005","Haziq Syafiq", "C-102","Robotics Club","Active");
    addRegistration("S-007","Nurul Ain",    "C-102","Robotics Club","Active");
    addRegistration("S-009","Kavitha",      "C-102","Robotics Club","Active");
    addRegistration("S-010","Izzatul Husna","C-102","Robotics Club","Waitlisted");
    addRegistration("S-001","Ahmad Farid",  "C-103","Scouts","Active");
    addRegistration("S-002","Siti Aisyah",  "C-103","Scouts","Active");
    addRegistration("S-004","Mei Ling",     "C-103","Scouts","Active");
    addRegistration("S-006","Priya Devi",   "C-103","Scouts","Active");
    addRegistration("S-008","Darren Lim",   "C-103","Scouts","Active");
    addRegistration("S-010","Izzatul Husna","C-103","Scouts","Active");
    addRegistration("S-002","Siti Aisyah",  "C-104","Badminton Club","Active");
    addRegistration("S-003","Rajendran",    "C-104","Badminton Club","Active");
    addRegistration("S-005","Haziq Syafiq", "C-104","Badminton Club","Active");
    addRegistration("S-009","Kavitha",      "C-104","Badminton Club","Active");
    addRegistration("S-006","Priya Devi",   "C-105","Art & Craft","Active");
}

// =============================================================
//  CLUB MANAGEMENT MENU
// =============================================================
void menuClub() {
    int choice;
    do {
        divider();
        sectionTitle("CLUB MANAGEMENT");
        cout << "  1. View All Clubs"             << endl;
        cout << "  2. Add New Club"               << endl;
        cout << "  3. Update Club Details"        << endl;
        cout << "  4. Cancel a Club"              << endl;
        cout << "  5. View Students in a Club"    << endl;
        cout << "  0. Back"                       << endl;
        choice = inputInt("  Choice: ", 0, 5);

        if (choice == 1) {
            divider();
            sectionTitle("ALL CLUBS");
            clubList.displayAll();
        }
        else if (choice == 2) {
            divider();
            sectionTitle("ADD NEW CLUB");
            string id   = inputString("  Club ID (e.g. C-106): ");
            string name = inputString("  Club Name: ");
            cout << "  Category: 1=Sports  2=Academic  3=Uniformed Body  4=Arts" << endl;
            int catChoice = inputInt("  Choose: ", 1, 4);
            string cat;
            if      (catChoice == 1) cat = CAT_SPORTS;
            else if (catChoice == 2) cat = CAT_ACADEMIC;
            else if (catChoice == 3) cat = CAT_UNIFORM;
            else                     cat = CAT_ARTS;
            int    cap   = inputInt("  Max Capacity: ", 1, 100);
            string room  = inputString("  Classroom/Venue: ");
            string time  = inputString("  Meeting Time (e.g. Mon 2:00PM): ");
            string teach = inputString("  Teacher-in-Charge Staff ID: ");
            clubList.addClub(Club(id, name, cat, cap, room, time, teach));
            cout << GREEN << "  Club added successfully." << RESET << endl;
        }
        else if (choice == 3) {
            divider();
            sectionTitle("UPDATE CLUB");
            clubList.displayAll();
            string id    = inputString("  Enter Club ID to update: ");
            string name  = inputString("  New Name: ");
            cout << "  Category: 1=Sports  2=Academic  3=Uniformed Body  4=Arts" << endl;
            int catChoice = inputInt("  Choose: ", 1, 4);
            string cat;
            if      (catChoice == 1) cat = CAT_SPORTS;
            else if (catChoice == 2) cat = CAT_ACADEMIC;
            else if (catChoice == 3) cat = CAT_UNIFORM;
            else                     cat = CAT_ARTS;
            int    cap   = inputInt("  New Capacity: ", 1, 100);
            string room  = inputString("  New Classroom: ");
            clubList.updateClub(id, name, cat, cap, room, "TBA", "TBA");
        }
        else if (choice == 4) {
            divider();
            sectionTitle("CANCEL CLUB");
            clubList.displayAll();
            string id = inputString("  Enter Club ID to cancel: ");
            // Confirmation prompt before cancelling
            if (confirmAction("Cancel club " + id + "? This cannot be undone")) {
                clubList.cancelClub(id);
            } else {
                cout << YELLOW << "  Cancelled. No changes made." << RESET << endl;
            }
        }
        else if (choice == 5) {
            divider();
            sectionTitle("VIEW STUDENTS IN CLUB");
            clubList.displayAll();
            string id = inputString("  Enter Club ID: ");
            clubList.displayStudentsInClub(id);
        }

    } while (choice != 0);
}

// =============================================================
//  STUDENT MANAGEMENT MENU
// =============================================================
void menuStudent() {
    int choice;
    do {
        divider();
        sectionTitle("STUDENT MANAGEMENT");
        cout << "  1. View All Students"            << endl;
        cout << "  2. Add New Student"              << endl;
        cout << "  3. Update Student Details"       << endl;
        cout << "  4. Delete Student"               << endl;
        cout << "  5. View Student's Registered Clubs" << endl;
        cout << "  0. Back"                         << endl;
        choice = inputInt("  Choice: ", 0, 5);

        if (choice == 1) {
            divider();
            sectionTitle("ALL STUDENTS");
            studentList.displayAll();
        }
        else if (choice == 2) {
            divider();
            sectionTitle("ADD NEW STUDENT");
            string id   = inputString("  Student ID (e.g. S-011): ");
            string name = inputString("  Full Name: ");
            int    age  = inputInt("  Age (7-12): ", 7, 12);
            int    year = inputInt("  Year Level (1-6): ", 1, 6);
            studentList.addStudent(Student(id, name, age, year));
        }
        else if (choice == 3) {
            divider();
            sectionTitle("UPDATE STUDENT");
            studentList.displayAll();
            string id   = inputString("  Enter Student ID to update: ");
            string name = inputString("  New Name: ");
            int    age  = inputInt("  New Age (7-12): ", 7, 12);
            int    year = inputInt("  New Year Level (1-6): ", 1, 6);
            studentList.updateStudent(id, name, age, year);
        }
        else if (choice == 4) {
            divider();
            sectionTitle("DELETE STUDENT");
            studentList.displayAll();
            string id = inputString("  Enter Student ID to delete: ");
            if (confirmAction("Permanently delete student " + id)) {
                studentList.deleteStudent(id);
            } else {
                cout << YELLOW << "  Cancelled. No changes made." << RESET << endl;
            }
        }
        else if (choice == 5) {
            divider();
            sectionTitle("VIEW STUDENT'S REGISTERED CLUBS");
            studentList.displayAll();
            string id = inputString("  Enter Student ID: ");
            Node* found = studentList.linearSearch(id);
            if (found == NULL) {
                cout << RED << "  Student ID \"" << id << "\" not found." << RESET << endl;
            } else {
                Student& s = found->data;
                cout << endl;
                cout << "  Student : " << s.getName() << " (" << s.getId() << ")" << endl;
                cout << "  Year    : " << s.getYearLevel() << endl;
                cout << "  " << string(35, '-') << endl;
                if (s.getClubCount() == 0) {
                    cout << "  This student has not registered for any clubs." << endl;
                } else {
                    cout << "  Registered Clubs (" << s.getClubCount() << "):" << endl;
                    for (int i = 0; i < s.getClubCount(); i++) {
                        string cid = s.getClubID(i);
                        Club* club = clubList.binarySearch(cid);
                        if (club != NULL)
                            cout << "  " << (i+1) << ". " << cid << " — " << club->getName() << endl;
                        else
                            cout << "  " << (i+1) << ". " << cid << endl;
                    }
                }
                cout << "  " << string(35, '-') << endl;
            }
        }

    } while (choice != 0);
}

// =============================================================
//  REGISTRATION MANAGEMENT MENU
// =============================================================
void menuRegistration() {
    int choice;
    do {
        divider();
        sectionTitle("REGISTRATION MANAGEMENT");
        cout << "  1. Register Student for Club" << endl;
        cout << "  2. Cancel Registration"       << endl;
        cout << "  3. View Club Waitlist"         << endl;
        cout << "  4. View Registration History" << endl;
        cout << "  0. Back"                       << endl;
        choice = inputInt("  Choice: ", 0, 4);

        if (choice == 1) {
            divider();
            sectionTitle("REGISTER STUDENT");
            cout << endl << "  -- Available Clubs --" << endl;
            clubList.displayAll();
            cout << endl << "  -- Students --" << endl;
            studentList.displayAll();

            string sid = inputString("  Enter Student ID: ");
            string cid = inputString("  Enter Club ID: ");

            Node* sNode = studentList.linearSearch(sid);
            if (sNode == NULL) {
                cout << RED << "  [Error] Student \"" << sid << "\" not found." << RESET << endl;
                continue;
            }

            string sName = sNode->data.getName();

            if (sNode->data.isRegisteredFor(cid)) {
                cout << RED << "  [Error] \"" << sName
                     << "\" is already registered for club " << cid << "." << RESET << endl;
                continue;
            }

            string result = clubList.enrollStudent(cid, sid, sName);

            if (result == "enrolled") {
                sNode->data.addClub(cid);
                Club* c = clubList.binarySearch(cid);
                string cName = (c != NULL) ? c->getName() : cid;
                addRegistration(sid, sName, cid, cName, "Active");
                cout << GREEN << "  SUCCESS: \"" << sName
                     << "\" enrolled in club " << cid << "." << RESET << endl;
            }
            else if (result == "waitlisted") {
                sNode->data.addClub(cid);
                Club* c = clubList.binarySearch(cid);
                string cName = (c != NULL) ? c->getName() : cid;
                addRegistration(sid, sName, cid, cName, "Waitlisted");
                cout << YELLOW << "  NOTICE: Club full. \"" << sName
                     << "\" added to waitlist." << RESET << endl;
            }
            else if (result == "not_found") {
                cout << RED << "  [Error] Club ID \"" << cid << "\" not found." << RESET << endl;
            }
            else if (result == "cancelled") {
                cout << RED << "  [Error] Club \"" << cid
                     << "\" has been cancelled." << RESET << endl;
            }
        }

        else if (choice == 2) {
            divider();
            sectionTitle("CANCEL REGISTRATION");
            studentList.displayAll();
            string sid = inputString("  Enter Student ID: ");
            string cid = inputString("  Enter Club ID to cancel: ");

            Node* sNode = studentList.linearSearch(sid);
            if (sNode == NULL) {
                cout << RED << "  [Error] Student \"" << sid
                     << "\" not found." << RESET << endl;
                continue;
            }

            if (!sNode->data.isRegisteredFor(cid)) {
                cout << RED << "  [Error] Student is not registered for club \""
                     << cid << "\"." << RESET << endl;
                continue;
            }

            string sName = sNode->data.getName();

            // Confirmation before cancelling
            if (!confirmAction("Cancel " + sName + "'s registration for club " + cid)) {
                cout << YELLOW << "  Cancelled. No changes made." << RESET << endl;
                continue;
            }

            string result = clubList.cancelEnrolment(cid, sid, sName);
            if (result == "cancelled") {
                sNode->data.removeClub(cid);
                cout << GREEN << "  Registration cancelled successfully." << RESET << endl;
            }
        }

        else if (choice == 3) {
            divider();
            sectionTitle("VIEW WAITLIST");
            clubList.displayAll();
            string cid = inputString("  Enter Club ID: ");
            clubList.displayWaitlist(cid);
        }

        else if (choice == 4) {
            divider();
            sectionTitle("REGISTRATION HISTORY");
            displayRegistrationHistory();
        }

    } while (choice != 0);
}

// =============================================================
//  SEARCH MENU
// =============================================================
void menuSearch() {
    int choice;
    do {
        divider();
        sectionTitle("SEARCH");
        cout << "  1. Search Student by ID   " << MAGENTA << "(Linear Search)" << RESET << endl;
        cout << "  2. Search Student by Name " << MAGENTA << "(Linear Search)" << RESET << endl;
        cout << "  3. Search Club by ID      " << MAGENTA << "(Binary Search)" << RESET << endl;
        cout << "  0. Back" << endl;
        choice = inputInt("  Choice: ", 0, 3);

        if (choice == 1) {
            string id = inputString("  Enter Student ID: ");
            Node* result = studentList.linearSearch(id);
            if (result != NULL) {
                cout << GREEN << endl << "  Found:" << RESET << endl;
                studentList.displayHeader();
                result->data.displayInfo();
            } else {
                cout << RED << "  Student ID \"" << id << "\" not found." << RESET << endl;
            }
        }
        else if (choice == 2) {
            string name = inputString("  Enter Student Name: ");
            Node* result = studentList.linearSearchByName(name);
            if (result != NULL) {
                cout << GREEN << endl << "  Found:" << RESET << endl;
                studentList.displayHeader();
                result->data.displayInfo();
            } else {
                cout << RED << "  Student name \"" << name << "\" not found." << RESET << endl;
            }
        }
        else if (choice == 3) {
            string id = inputString("  Enter Club ID (e.g. C-103): ");
            Club* result = clubList.binarySearch(id);
            if (result != NULL) {
                cout << GREEN << endl << "  Found:" << RESET << endl;
                result->displayFull();
            } else {
                cout << RED << "  Club ID \"" << id << "\" not found." << RESET << endl;
            }
        }

    } while (choice != 0);
}

// =============================================================
//  REPORTS MENU
// =============================================================
void menuReports() {
    int choice;
    do {
        divider();
        sectionTitle("REPORTS");
        cout << "  1. Club Popularity & Capacity Report" << endl;
        cout << "     " << MAGENTA << "(sort by Club ID or Total Students Enrolled)"
             << RESET << endl;
        cout << "  0. Back" << endl;
        choice = inputInt("  Choice: ", 0, 1);

        if (choice == 1) {
            clubList.displayReport();
        }

    } while (choice != 0);
}

// =============================================================
//  main()
// =============================================================
// =============================================================
//  STUDENT PORTAL  —  limited access for logged-in student
// =============================================================
void menuStudentPortal(const string& studentID, const string& studentName) {
    int choice;
    do {
        divider();
        cout << GREEN << "  Logged in as: " << studentName << " (" << studentID << ")" << RESET << endl;
        sectionTitle("STUDENT PORTAL");
        cout << "  1. View Available Clubs"     << endl;
        cout << "  2. Register for a Club"      << endl;
        cout << "  3. Cancel My Registration"   << endl;
        cout << "  4. View My Registered Clubs" << endl;
        cout << "  5. Search Club by ID"        << endl;
        cout << "  0. Logout"                   << endl;
        choice = inputInt("  Choice: ", 0, 5);

        if (choice == 1) {
            divider();
            sectionTitle("AVAILABLE CLUBS");
            clubList.displayAll();
        }
        else if (choice == 2) {
            divider();
            sectionTitle("REGISTER FOR CLUB");
            clubList.displayAll();
            string cid = inputString("  Enter Club ID: ");
            Node* sNode = studentList.linearSearch(studentID);
            if (sNode == NULL) { cout << RED << "  [Error] Account not found." << RESET << endl; continue; }
            if (sNode->data.isRegisteredFor(cid)) {
                cout << RED << "  [Error] You are already registered for club " << cid << "." << RESET << endl;
                continue;
            }
            string result = clubList.enrollStudent(cid, studentID, studentName);
            if (result == "enrolled") {
                sNode->data.addClub(cid);
                Club* c = clubList.binarySearch(cid);
                addRegistration(studentID, studentName, cid, (c ? c->getName() : cid), "Active");
                cout << GREEN << "  SUCCESS: Enrolled in club " << cid << "." << RESET << endl;
            } else if (result == "waitlisted") {
                sNode->data.addClub(cid);
                Club* c = clubList.binarySearch(cid);
                addRegistration(studentID, studentName, cid, (c ? c->getName() : cid), "Waitlisted");
                cout << YELLOW << "  NOTICE: Club full. You have been added to the waitlist." << RESET << endl;
            } else if (result == "not_found") {
                cout << RED << "  [Error] Club ID \"" << cid << "\" not found." << RESET << endl;
            } else if (result == "cancelled") {
                cout << RED << "  [Error] That club has been cancelled." << RESET << endl;
            }
        }
        else if (choice == 3) {
            divider();
            sectionTitle("CANCEL MY REGISTRATION");
            Node* sNode = studentList.linearSearch(studentID);
            if (sNode == NULL) { cout << RED << "  [Error] Account not found." << RESET << endl; continue; }
            if (sNode->data.getClubCount() == 0) {
                cout << YELLOW << "  You are not registered for any clubs." << RESET << endl;
                continue;
            }
            cout << "  Your registered clubs:" << endl;
            cout << "  " << string(35, '-') << endl;
            for (int i = 0; i < sNode->data.getClubCount(); i++) {
                string cid = sNode->data.getClubID(i);
                Club* c = clubList.binarySearch(cid);
                cout << "  " << (i+1) << ". " << cid;
                if (c) cout << " — " << c->getName();
                cout << endl;
            }
            cout << "  " << string(35, '-') << endl;
            string cid = inputString("  Enter Club ID to cancel: ");
            if (!sNode->data.isRegisteredFor(cid)) {
                cout << RED << "  [Error] You are not registered for club " << cid << "." << RESET << endl;
                continue;
            }
            string result = clubList.cancelEnrolment(cid, studentID, studentName);
            if (result == "cancelled") {
                sNode->data.removeClub(cid);
                cout << GREEN << "  Registration for " << cid << " cancelled." << RESET << endl;
            }
        }
        else if (choice == 4) {
            divider();
            sectionTitle("MY REGISTERED CLUBS");
            Node* sNode = studentList.linearSearch(studentID);
            if (sNode == NULL) { cout << RED << "  [Error] Account not found." << RESET << endl; continue; }
            Student& s = sNode->data;
            cout << "  Student : " << s.getName() << " (" << s.getId() << ")" << endl;
            cout << "  Year    : " << s.getYearLevel() << endl;
            cout << "  " << string(35, '-') << endl;
            if (s.getClubCount() == 0) {
                cout << "  You have not registered for any clubs." << endl;
            } else {
                cout << "  Registered Clubs (" << s.getClubCount() << "):" << endl;
                for (int i = 0; i < s.getClubCount(); i++) {
                    string cid = s.getClubID(i);
                    Club* c = clubList.binarySearch(cid);
                    cout << "  " << (i+1) << ". " << cid;
                    if (c) cout << " — " << c->getName();
                    cout << endl;
                }
            }
            cout << "  " << string(35, '-') << endl;
        }
        else if (choice == 5) {
            divider();
            sectionTitle("SEARCH CLUB BY ID");
            string id = inputString("  Enter Club ID: ");
            Club* result = clubList.binarySearch(id);
            if (result != NULL) {
                cout << GREEN << endl << "  Found:" << RESET << endl;
                result->displayFull();
            } else {
                cout << RED << "  Club ID \"" << id << "\" not found." << RESET << endl;
            }
        }
    } while (choice != 0);
    cout << YELLOW << "  Logged out. Goodbye, " << studentName << "!" << RESET << endl;
}

// =============================================================
//  TEACHER PORTAL  —  full access
// =============================================================
void menuTeacher(const string& teacherName) {
    int choice;
    do {
        divider();
        cout << GREEN << "  Logged in as: " << teacherName << " (Teacher)" << RESET << endl;
        sectionTitle("TEACHER PORTAL");
        cout << "  1. Club Management"    << endl;
        cout << "  2. Student Management" << endl;
        cout << "  3. Registration"       << endl;
        cout << "  4. Search"             << endl;
        cout << "  5. Reports"            << endl;
        cout << "  0. Logout"             << endl;
        choice = inputInt("  Choice: ", 0, 5);
        if      (choice == 1) menuClub();
        else if (choice == 2) menuStudent();
        else if (choice == 3) menuRegistration();
        else if (choice == 4) menuSearch();
        else if (choice == 5) menuReports();
    } while (choice != 0);
    cout << YELLOW << "  Logged out. Goodbye, " << teacherName << "!" << RESET << endl;
}

// =============================================================
//  main()
// =============================================================
int main() {
    cout << YELLOW << "  Loading preset data..." << RESET;
    loadPresetData();
    cout << GREEN << "  Done! " << RESET << "5 clubs and 10 students loaded." << endl;

    int choice;
    do {
        divider();
        cout << "  =============================================" << endl;
        cout << "    PrimCoQ — Primary School Co-Curriculum     " << endl;
        cout << "              Management System                " << endl;
        cout << "  =============================================" << endl;
        cout << endl;
        cout << "  1. Login as Teacher" << endl;
        cout << "  2. Login as Student" << endl;
        cout << "  0. Exit"             << endl;
        choice = inputInt("  Choice: ", 0, 2);

        if (choice == 1) {
            divider();
            sectionTitle("TEACHER LOGIN");
            string staffID  = inputString("  Staff ID  : ");
            string password = inputString("  Password  : ");
            string name = auth.loginTeacher(staffID, password);
            if (name.empty()) {
                cout << RED << "  [Error] Invalid Staff ID or password." << RESET << endl;
            } else {
                cout << GREEN << "  Login successful! Welcome, " << name << "." << RESET << endl;
                menuTeacher(name);
            }
        }
        else if (choice == 2) {
            divider();
            sectionTitle("STUDENT LOGIN");
            string sid = inputString("  Enter your Student ID: ");
            Node* found = studentList.linearSearch(sid);
            if (found == NULL) {
                cout << RED << "  [Error] Student ID \"" << sid << "\" not found." << RESET << endl;
            } else {
                string sName = found->data.getName();
                cout << GREEN << "  Login successful! Welcome, " << sName << "." << RESET << endl;
                menuStudentPortal(sid, sName);
            }
        }
    } while (choice != 0);

    cout << endl << CYAN
         << "     Thank you for using PrimCoQ!      " << endl
         << "     Goodbye!                          " << endl
         << RESET << endl << endl;
    return 0;
}
