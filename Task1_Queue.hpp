#ifndef TASK1_QUEUE_HPP
#define TASK1_QUEUE_HPP

#include <iostream>
#include <string>

using namespace std;

// Student node structure
struct StudentNode {
    string studentID;
    string name;
    StudentNode* next;

    StudentNode(string id, string n) : studentID(id), name(n), next(nullptr) {}
};

// Queue class declaration
class RegistrationQueue {
private:
    StudentNode* front;
    StudentNode* rear;

public:
    RegistrationQueue();
    void enqueue(string id, string name);
    StudentNode* dequeue();
    bool isEmpty();
    void display();
};

// management statement
class Task1Manager {
private:
    StudentNode* activeSession[3]; 
    bool slotOccupied[3];
    RegistrationQueue waitingQueue;

public:
    Task1Manager();
    void loadFromCSV();
    void registerLearner(string id, string name);
    void autoFillSession();
    void logoutLearner(int slot);
    void showStatus();
    
    bool isStudentActive(string id); 
};

// Call function globally
void runTask1Module();

extern Task1Manager globalManager; // Makes the manager visible to Task 2
#endif