#ifndef TASK3_LOG_HPP
#define TASK3_LOG_HPP

#include "Activity.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// This class represents an Array-based Circular Queue for Activity Logs
class ActivityLogQueue {
private:
    Activity* logArray; // Dynamically allocated array
    int capacity;       // Maximum fixed capacity of the log
    int front;          // Index pointing to the oldest record
    int rear;           // Index pointing to the newest record
    int count;          // Current number of log entries

public:
    // Constructor: Sets fixed capacity, defaults to 100 records
    ActivityLogQueue(int size = 100);
    
    // Destructor: Frees allocated memory
    ~ActivityLogQueue();

    // Core queue operations
    void addLog(string id, string course, int time, int score, int attempt);
    void displayAllLogs();
    void filterLogsByStudent(string targetID);
    void exportToCSV(string filename);
};

// Global function to run Task 3 module from main.cpp
void runTask3Module();

#endif