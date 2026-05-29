#include "Person.h"
#include <iostream>
using namespace std;

// =============================================================
//  Person.cpp  —  Implementation of Person base class
// =============================================================

// ---------- Constructors ----------
Person::Person() : id(""), name(""), age(0) {}

Person::Person(string id, string name, int age)
    : id(id), name(name), age(age) {}

// ---------- Destructor ----------
Person::~Person() {}

// ---------- Getters ----------
string Person::getId()   const { return id;   }
string Person::getName() const { return name; }
int    Person::getAge()  const { return age;  }

// ---------- Setters ----------
void Person::setId(string id)     { this->id   = id;   }
void Person::setName(string name) { this->name = name; }
void Person::setAge(int age)      { this->age  = age;  }
