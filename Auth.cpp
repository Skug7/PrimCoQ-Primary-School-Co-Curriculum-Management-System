#include "Auth.h"
#include <iostream>
using namespace std;

// =============================================================
//  Auth.cpp  —  Login system implementation
// =============================================================

Auth::Auth() : accountCount(0) {
    // Hardcoded teacher accounts (like preset data)
    accounts[0] = {"T-001", "pass123", "Mr. Rahman"};
    accounts[1] = {"T-002", "pass123", "Ms. Lim"};
    accounts[2] = {"T-003", "pass123", "Mr. Suresh"};
    accounts[3] = {"T-004", "pass123", "Ms. Farah"};
    accountCount = 4;
}

// Returns teacher name if credentials match, "" if not found
string Auth::loginTeacher(const string& staffID, const string& password) const {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].staffID == staffID &&
            accounts[i].password == password) {
            return accounts[i].name;
        }
    }
    return "";
}

int Auth::getAccountCount() const { return accountCount; }

string Auth::getTeacherName(const string& staffID) const {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].staffID == staffID)
            return accounts[i].name;
    }
    return "";
}
