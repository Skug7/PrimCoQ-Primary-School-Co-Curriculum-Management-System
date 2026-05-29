#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

// =============================================================
//  Person.h  —  Abstract base class for Student and Teacher
//  Demonstrates: Encapsulation, Inheritance, Polymorphism
// =============================================================

class Person {
private:
    // Private attributes — only accessible via getters/setters (encapsulation)
    string id;
    string name;
    int    age;

public:
    // ---------- Constructors ----------
    Person();                                        // Default constructor
    Person(string id, string name, int age);         // Parameterised constructor

    // ---------- Destructor ----------
    virtual ~Person();    // Virtual destructor — ensures proper cleanup in derived classes

    // ---------- Getters (Accessors) ----------
    string getId()   const;
    string getName() const;
    int    getAge()  const;

    // ---------- Setters (Mutators) ----------
    void setId(string id);
    void setName(string name);
    void setAge(int age);

    // ---------- Pure Virtual Function ----------
    // Forces every derived class (Student, Teacher) to implement its own display
    // This is what gives us POLYMORPHISM — same function call, different behaviour
    virtual void displayInfo() const = 0;
};

#endif
