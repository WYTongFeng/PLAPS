#ifndef TASK2_NAV_HPP
#define TASK2_NAV_HPP

#include "Activity.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class SessionFlow {
private:
    Activity* head;
    Activity* current;
    Activity* tail;

    // Helper to add a question node to our Doubly Linked List
    void addQuestion(string studentID, string course);

public:
    SessionFlow();
    ~SessionFlow();

    // Builds the sequence of questions based on chosen topic
    void buildQuiz(string studentID, string topic);
    
    // Starts the interactive navigation loop
    void startSession();

    // Saves the session logs to log queue for Task 3
    void saveToLogQueue();
};

void runTask2Module();

#endif