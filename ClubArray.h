#ifndef CLUBARRAY_H
#define CLUBARRAY_H

#include "Club.h"
#include "Queue.h"
#include <string>
using namespace std;

const int MAX_CLUBS = 50;

class ClubArray {
private:
    Club  clubs[MAX_CLUBS];       
    Queue waitlists[MAX_CLUBS];   
    int   count;                  

    int findIndex(const string& clubID) const;  

public:
    ClubArray();

    bool addClub   (Club c);
    void displayAll() const;
    bool updateClub(const string& clubID,
                    const string& newName,
                    const string& newCategory,
                    int           newCapacity,
                    const string& newClassroom,
                    const string& newTime,
                    const string& newTeacher);
    bool cancelClub(const string& clubID);   

    string enrollStudent (const string& clubID, const string& studentID, const string& studentName);
    string cancelEnrolment(const string& clubID, const string& studentID, const string& studentName);
    void   displayWaitlist(const string& clubID);
    void   displayStudentsInClub(const string& clubID);  // NEW

    Club* binarySearch(const string& clubID);

    void sortBy(const string& key);

    void displayReport();   

    int  getCount() const;
    bool isFull()   const;
    void displayHeader() const;
};

#endif
