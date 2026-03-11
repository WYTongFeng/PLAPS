#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <string>
using namespace std;

struct Activity {
    string studentID;     // Maps to CSV: StudentID
    string courseName;    // Maps to CSV: CourseName
    int timeSpent;        // Maps to CSV: TimeSpent (in minutes)
    int score;            // Maps to CSV: Score
    int attemptNumber;    // Maps to CSV: AttemptNumber (1, 2, or 3 max)

    // Pointers for building the Stack or Doubly Linked List in Task 2
    Activity* next;
    Activity* prev;

    // Constructor updated to match the 5 variables
    Activity(string sID = "", string cName = "", int time = 0, int s = 0, int att = 1) {
        studentID = sID;
        courseName = cName;
        timeSpent = time;
        score = s;
        attemptNumber = att;
        next = nullptr;
        prev = nullptr;
    }
};

#endif