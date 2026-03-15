#ifndef TASK4_PRIORITY_HPP
#define TASK4_PRIORITY_HPP

#include "Student.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class AtRiskPriorityQueue {
private:
    Student* head;

public:
    AtRiskPriorityQueue();
    void analyzeAndInsert(string id, string name, int score, int timeSpent, int attempt);
    void enqueue(string id, string name, int risk, string rec);
    void displayQueue();
    void exportToCSV();
    string getStudentNameFromCSV(string searchID);
    void loadFromLogsCSV(string filename);
    void clearQueue();
};

void runTask4Module();

#endif