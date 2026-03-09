#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <string>
using namespace std;

// This struct acts as the blueprint for every learning activity.
// Task 2 will use this to navigate, and Task 3 will use this to write the logs.csv file.
struct Activity {
    string activityID;
    string topic;         // e.g., "Arrays", "Linked Lists"
    string difficulty;    // e.g., "Easy", "Medium", "Hard"
    int score;            // The student's score 

    // Pointers for building the Stack or Doubly Linked List in Task 2
    Activity* next;
    Activity* prev;

    // Constructor
    Activity(string id = "", string t = "", string diff = "", int s = 0) {
        activityID = id;
        topic = t;
        difficulty = diff;
        score = s;
        next = nullptr;
        prev = nullptr;
    }
};

#endif