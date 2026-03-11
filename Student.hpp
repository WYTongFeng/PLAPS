#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
using namespace std;

struct Student {
    string studentID;         // Maps to students.csv & at_risk_students.csv
    string name;              // Maps to students.csv
    int riskScore;            // Maps to at_risk_students.csv
    string recommendation;    // Maps to at_risk_students.csv (Renamed to match CSV)
    
    // Pointers for building custom linked lists, queues, or stacks
    Student* next;         
    Student* prev;         

    // Constructor
    Student(string id = "", string n = "", int risk = 0, string rec = "None") {
        studentID = id;
        name = n;
        riskScore = risk;
        recommendation = rec;
        next = nullptr;
        prev = nullptr;
    }
};

#endif