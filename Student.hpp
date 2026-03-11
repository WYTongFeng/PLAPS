#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
using namespace std;

struct Student {
    string studentID;         // e.g., "TP012345"
    string name;              // e.g., "Ali"
    int riskScore;            // Used by Task 4 (Priority Queue)
    string recommendedAction; // NEW: Required for Task 4's CSV export
    
    // Pointers for building custom linked lists, queues, or stacks
    Student* next;         
    Student* prev;         

    // Constructor
    Student(string id = "", string n = "", int risk = 0, string action = "None") {
        studentID = id;
        name = n;
        riskScore = risk;
        recommendedAction = action;
        next = nullptr;
        prev = nullptr;
    }
};

#endif