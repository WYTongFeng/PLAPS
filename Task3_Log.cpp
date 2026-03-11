#ifndef TASK3_LOG_HPP
#define TASK3_LOG_HPP

#include "Activity.hpp"
#include <iostream>
using namespace std;

// The assignment asks for a "fixed-size" log. 
// Let's set it to 10 for testing. If a student does 11 activities, 
// the 1st one is deleted to make room for the 11th.
const int MAX_LOG_CAPACITY = 10; 

struct CircularLogQueue {
    Activity logs[MAX_LOG_CAPACITY]; // The fixed-size array
    int head; // Points to the oldest log
    int tail; // Points to the newest log
    int count; // How many logs are currently stored

    CircularLogQueue() {
        head = 0;
        tail = -1;
        count = 0;
    }

    // THE CRITICAL FUNCTION: Adding logs and replacing old ones
    void addActivityLog(Activity newActivity) {
        // Use modulo (%) to wrap the tail back to 0 if it hits the limit
        tail = (tail + 1) % MAX_LOG_CAPACITY;
        
        // Store the new activity at the new tail position
        logs[tail] = newActivity;

        if (count < MAX_LOG_CAPACITY) {
            // If the log isn't full yet, just increase the count
            count++;
        } else {
            // IF THE LOG IS FULL: The tail just overwrote the oldest record!
            // So, we must push the head forward by 1 so it points to the new "oldest" record.
            head = (head + 1) % MAX_LOG_CAPACITY;
        }
    }

    // Function to print all current logs
    void displayLogs() {
        if (count == 0) {
            cout << "Activity log is empty.\n";
            return;
        }
        
        cout << "\n--- Recent Activity Logs ---\n";
        for (int i = 0; i < count; i++) {
            // Use modulo to correctly read from head to tail in a circle
            int index = (head + i) % MAX_LOG_CAPACITY;
            cout << "Attempt " << logs[index].attemptNumber << " | ";
            cout << "Course: " << logs[index].courseName << " | ";
            cout << "Score: " << logs[index].score << "\n";
        }
    }
};

#endif