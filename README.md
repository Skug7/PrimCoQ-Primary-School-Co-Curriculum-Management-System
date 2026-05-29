# PrimCoQ — Primary School Co-Curriculum Management System

> TMF1434 Data Structures & Algorithms 
> Universiti Malaysia Sarawak (UNIMAS)

---

## 📌 About

PrimCoQ is a console-based C++ system that manages co-curricular club activities for a primary school. It supports two user roles — **Teacher** (full access) and **Student** (limited access) — with a login system at startup.

---

## ✨ Features

### Teacher Portal
- Add, update, cancel, and view clubs
- Add, update, delete, and view students
- Register students for clubs / cancel registrations
- View students enrolled in a specific club
- View registration history
- Search student by ID or name (Linear Search)
- Search club by ID (Binary Search)
- Club Popularity & Capacity Report (sorted by Club ID or Total Enrolled)

### Student Portal
- View available clubs
- Register for a club
- Cancel own registration
- View own registered clubs
- Search club by ID (Binary Search)

### Automatic Waitlist
- When a club is full, new registrations are automatically queued (FIFO)
- When a student cancels, the first person on the waitlist is automatically promoted

---

## 🗂️ Data Structures Used

| Structure | Used For | Reason |
|---|---|---|
| Array (`ClubArray`) | Storing clubs (max 50) | Fixed size; enables Binary Search |
| Array (`regHistory`) | Registration history (max 200) | Simple sequential storage |
| Linked List | Storing student records | Dynamic size; efficient insert/delete |
| Queue (FIFO) | Waitlist per club | First-come-first-served ordering |

> ⚠️ No STL containers were used. All data structures are implemented from scratch.

---

## 🔍 Algorithms Used

| Algorithm | Applied To | Time Complexity |
|---|---|---|
| Linear Search | Student list (Linked List) | O(n) |
| Binary Search | Club list (sorted Array) | O(log n) |
| Bubble Sort | Club Popularity Report (2 keys) | O(n²) |

---

## 🏗️ OOP Design

```
Person  (abstract base class)
  ├── Student  (inherits Person)
  └── Teacher  (inherits Person)

Club          (stored in ClubArray)
Registration  (stored in regHistory[])
Auth          (handles login logic)
```

- **Encapsulation** — all attributes are private with getters/setters
- **Inheritance** — Student and Teacher inherit from Person
- **Polymorphism** — `displayInfo()` is a pure virtual function overridden by each subclass

---

## 🗃️ File Structure

```
PrimCoQ/
  ├── Auth.h / Auth.cpp           ← Login system
  ├── Person.h / Person.cpp       ← Abstract base class
  ├── Student.h / Student.cpp     ← Inherits Person
  ├── Teacher.h / Teacher.cpp     ← Inherits Person
  ├── Club.h / Club.cpp           ← Club entity
  ├── Registration.h / Registration.cpp
  ├── Node.h                      ← Linked list node
  ├── LinkedList.h / LinkedList.cpp
  ├── QueueNode.h                 ← Queue node
  ├── Queue.h / Queue.cpp         ← FIFO waitlist
  ├── ClubArray.h / ClubArray.cpp ← Array + Binary Search + Sort
  └── main.cpp                    ← Entry point, menus, login
```

---

## 🚀 How to Run

### Using VSCode
1. Open the project folder in VSCode
2. Make sure all `.h` and `.cpp` files are in the same folder
3. Press `Ctrl + Shift + B` to compile and run

### Using Command Line
```bash
g++ *.cpp -o main.exe -std=c++17 -Wall
./main.exe
```

### Using DevC++
1. File → New → Project → Console Application → C++
2. Add all `.cpp` files to the project
3. Press `F9` to compile and run

---

## 🔑 Login Credentials

### Teacher Accounts
| Staff ID | Password |
|---|---|
| T-001 | pass123 |
| T-002 | pass123 |
| T-003 | pass123 |
| T-004 | pass123 |

### Student Accounts
Login using your **Student ID** (no password required).  
Preset student IDs: `S-001` to `S-010`

---

## 📦 Preset Data

The system loads the following data automatically on startup:

**5 Clubs**
| Club ID | Name | Category | Capacity |
|---|---|---|---|
| C-101 | Football Team | Sports | 10 |
| C-102 | Robotics Club | Academic | 5 |
| C-103 | Scouts | Uniformed Body | 8 |
| C-104 | Badminton Club | Sports | 6 |
| C-105 | Art & Craft | Arts & Culture | 4 |

**10 Students** — S-001 to S-010, pre-enrolled in various clubs.  
C-101 (Football) and C-102 (Robotics) are pre-filled to demonstrate the waitlist feature.

---
