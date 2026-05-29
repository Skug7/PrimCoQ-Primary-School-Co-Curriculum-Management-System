#ifndef AUTH_H
#define AUTH_H

#include <string>
using namespace std;

// =============================================================
//  Auth.h  —  Login system for PrimCoQ
//
//  Two roles:
//    Teacher  — Staff ID + Password, full access
//    Student  — Student ID only, limited access
// =============================================================

const int MAX_TEACHER_ACCOUNTS = 10;

struct TeacherAccount {
    string staffID;
    string password;
    string name;
};

class Auth {
private:
    TeacherAccount accounts[MAX_TEACHER_ACCOUNTS];
    int            accountCount;

public:
    Auth();

    // Returns teacher name if login success, "" if fail
    string loginTeacher(const string& staffID, const string& password) const;

    // Returns true if studentID exists in the system
    // (checked against LinkedList from main)
    bool   loginStudent(const string& studentID) const;

    // Getters
    int    getAccountCount() const;
    string getTeacherName(const string& staffID) const;
};

#endif
