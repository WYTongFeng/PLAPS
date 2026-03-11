#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <string>
using namespace std;

struct Activity {
    string logID;         // e.g., "LOG001"
    string studentID;     // NEW: Required so Task 3 knows who did the activity
    string topic;         // e.g., "Arrays"
    string difficulty;    // e.g., "Easy", "Hard"
    int score;            // Student's score for this activity

    // Pointers for building the Stack or Doubly Linked List in Task 2
    Activity* next;
    Activity* prev;

    // Constructor
    Activity(string lID = "", string sID = "", string t = "", string diff = "", int s = 0) {
        logID = lID;
        studentID = sID;
        topic = t;
        difficulty = diff;
        score = s;
        next = nullptr;
        prev = nullptr;
    }
};

#endif