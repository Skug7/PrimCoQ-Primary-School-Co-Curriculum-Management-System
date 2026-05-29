#ifndef CLUB_H
#define CLUB_H

#include <string>
using namespace std;

const string CAT_SPORTS   = "Sports";
const string CAT_ACADEMIC = "Academic";
const string CAT_UNIFORM  = "Uniformed Body";
const string CAT_ARTS     = "Arts & Culture";

class Club {
private:
    string clubID;           
    string name;             
    string category;        
    int    capacity;         
    int    enrolledCount;    

    string classroom;       
    string meetingTime;      
    string teacherInCharge;  

    bool   isActive;

    // Tracks which students are enrolled (parallel to enrolledCount)
    string enrolledStudentIDs[50];

public:
    Club();

    Club(const string& id,   const string& nm,
         const string& cat,  int           cap,
         const string& room, const string& time,
         const string& teacher);

    string getClubID()          const;
    string getName()            const;
    string getCategory()        const;
    int    getCapacity()        const;
    int    getEnrolledCount()   const;
    int    getAvailableSlots()  const;   
    string getClassroom()       const;
    string getMeetingTime()     const;
    string getTeacherInCharge() const;
    bool   getIsActive()        const;

    bool setClubID         (const string& id);
    bool setName           (const string& nm);
    bool setCategory       (const string& cat);
    bool setCapacity       (int cap);         
    bool setClassroom      (const string& room);
    bool setMeetingTime    (const string& time);
    bool setTeacherInCharge(const string& teacher);
    void setIsActive       (bool active);   

    bool enrol(const string& studentID = "");  // now accepts optional studentID
    bool unenrol(const string& studentID = ""); 

    bool   isFull()         const;   
    bool   isAvailable()    const;  
    string getStatusLabel() const;   

    bool operator==(const Club& other) const;
    bool operator< (const Club& other) const; 
    bool operator> (const Club& other) const; 

    bool hasMoreEnrolledThan(const Club& other) const;

    void displayRow()  const;
    void displayFull() const;
    void displayEnrolledStudents() const;  // NEW: list all students in this club
};

#endif