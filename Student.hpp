#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
using namespace std;

// This struct acts as the blueprint for every student in the system.
// Because you are building custom data structures (like Linked Lists), 
// we include a 'next' pointer right inside the struct to make things easier.
struct Student {
    string studentID;
    string name;
    int riskScore;         // Used by Task 4 (Priority Queue)
    int currentActivityID; // Used by Task 2 & 3
    
    // Pointers for building custom linked lists, queues, or stacks
    Student* next;         
    Student* prev;         // Useful if Task 2 uses a Doubly Linked List

    // Constructor to easily create a new student
    Student(string id = "", string n = "", int risk = 0) {
        studentID = id;
        name = n;
        riskScore = risk;
        currentActivityID = 0;
        next = nullptr;
        prev = nullptr;
    }
};

#endif