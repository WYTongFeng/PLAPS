//Task 4: At-Risk Learner Priority & Recommendation Engine
#ifndef TASK4_PRIORITY_HPP
#define TASK4_PRIORITY_HPP

#include "Student.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// This class is our custom Priority Queue 
class AtRiskPriorityQueue {
private:
    Student* head; // Points to the front of the queue (the most at-risk student)

public:
    // Constructor: Starts with an empty queue
    AtRiskPriorityQueue() {
        head = nullptr;
    }

    // ---------------------------------------------------------
    // Function 1: Calculate Risk Score & Generate Recommendation
    // ---------------------------------------------------------
    // We pass the student's activity data to calculate how much they are struggling.
    void analyzeAndInsert(string id, string name, int score, int timeSpent, int attempt) {
        int calculatedRisk = 0;
        string rec = "Keep up the good work!"; // Default recommendation

        // Rule 1: Low score adds high risk
        if (score < 40) {
            calculatedRisk += 50;
            rec = "Urgent: Repeat the entire topic immediately.";
        } else if (score < 60) {
            calculatedRisk += 30;
            rec = "Review the study materials and try an easier activity.";
        }

        // Rule 2: Too many attempts means they are stuck
        if (attempt >= 3) {
            calculatedRisk += 20;
            rec = "Please consult the lecturer for 1-to-1 help.";
        }

        // Rule 3: Spending too much time but getting low score
        if (timeSpent > 60 && score < 50) {
            calculatedRisk += 10;
        }

        // After calculating, insert this student into the Priority Queue
        enqueue(id, name, calculatedRisk, rec);
    }

    // ---------------------------------------------------------
    // Function 2: Insert into Priority Queue (The Core Logic!)
    // ---------------------------------------------------------
    // High risk score goes to the FRONT of the queue.
    void enqueue(string id, string name, int risk, string rec) {
        // Step 1: Create a new Student node
        Student* newStudent = new Student(id, name, risk, rec);

        // Step 2: Check if queue is empty, OR if the new student has the HIGHEST risk
        if (head == nullptr || risk > head->riskScore) {
            // Put the new student at the very front
            newStudent->next = head;
            head = newStudent;
        } 
        // Step 3: Otherwise, find the correct position in the middle or end
        else {
            Student* current = head;
            
            // Keep moving forward as long as the next student's risk is higher than ours
            while (current->next != nullptr && current->next->riskScore >= risk) {
                current = current->next;
            }
            
            // Insert the new student right after the 'current' student
            newStudent->next = current->next;
            current->next = newStudent;
        }
    }

    // ---------------------------------------------------------
    // Function 3: Display the Queue in the Console
    // ---------------------------------------------------------
    void displayQueue() {
        if (head == nullptr) {
            cout << "No at-risk students currently.\n";
            return;
        }

        cout << "\n=== At-Risk Learners Priority List ===\n";
        Student* current = head;
        int rank = 1;

        // Traverse the linked list and print
        while (current != nullptr) {
            cout << rank << ". [" << current->studentID << "] " << current->name 
                 << " | Risk Score: " << current->riskScore << "\n"
                 << "   Recommendation: " << current->recommendation << "\n";
            
            current = current->next;
            rank++;
        }
    }

    // ---------------------------------------------------------
    // Function 4: Export data to CSV (Task 4 Requirement)
    // ---------------------------------------------------------
    void exportToCSV() {
        // Open the file to write (this will overwrite old data)
        ofstream outFile("at_risk_students.csv");

        if (!outFile) {
            cout << "Error opening file for writing!\n";
            return;
        }

        // Write the CSV Header
        outFile << "StudentID,RiskScore,Recommendation\n";

        // Traverse the linked list and write to file
        Student* current = head;
        while (current != nullptr) {
            outFile << current->studentID << "," 
                    << current->riskScore << "," 
                    << current->recommendation << "\n";
            
            current = current->next;
        }

        outFile.close();
        cout << "[System] Successfully exported to at_risk_students.csv!\n";
    }

// ---------------------------------------------------------
    // Function 5: Find Student Name from student.csv
    // ---------------------------------------------------------
    string getStudentNameFromCSV(string searchID) {
        ifstream studentFile("student.csv");
        if (!studentFile.is_open()) {
            cout << "[Warning] Could not open student.csv! Using default name.\n";
            return "Learner"; 
        }

        string line;
        getline(studentFile, line); // Skip the first row of the table header (StudentID, Name)

        while (getline(studentFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string id, name;
            
            // Separate by comma
            getline(ss, id, ',');
            getline(ss, name, ',');

            //Remove any hidden spaces or newlines that may be present in id and searchID
            id.erase(0, id.find_first_not_of(" \r\n\t"));
            id.erase(id.find_last_not_of(" \r\n\t") + 1);
            searchID.erase(0, searchID.find_first_not_of(" \r\n\t"));
            searchID.erase(searchID.find_last_not_of(" \r\n\t") + 1);

            // If the match is successful
            if (id == searchID) {
                // Remove extra spaces before the name
                name.erase(0, name.find_first_not_of(" \r\n\t"));
                studentFile.close();
                return name; 
            }
        }

        studentFile.close();
        return "Unknown"; // The file is open, but the student ID is not found inside.
    }

    // ---------------------------------------------------------
    // Function 6: Read data from logs.csv (Real Data Integration)
    // ---------------------------------------------------------
    void loadFromLogsCSV(string filename) {
        ifstream file(filename);
        
        if (!file.is_open()) {
            cout << "[Error] Could not open " << filename << "!\n";
            return;
        }

        string line;
        // Step 1: Skip the header row (StudentID,CourseName,TimeSpent,Score,AttemptNumber)
        getline(file, line); 

        int loadedCount = 0;

        // Step 2: Read file line by line
        while (getline(file, line)) {
            // Skip empty lines
            if (line.empty()) continue; 

            stringstream ss(line);
            string id, course, timeStr, scoreStr, attemptStr;

            // Step 3: Split the line by commas (',')
            getline(ss, id, ',');
            getline(ss, course, ',');
            getline(ss, timeStr, ',');
            getline(ss, scoreStr, ',');
            getline(ss, attemptStr, ',');

            // Step 4: Convert string to integer (stoi)
            int timeSpent = stoi(timeStr);
            int score = stoi(scoreStr);
            int attempt = stoi(attemptStr);

            // Step 5: Send this real data into our Priority Queue!
            // (Note: logs.csv doesn't have names, so we just use "Learner" temporarily)
            string realName = getStudentNameFromCSV(id);
            analyzeAndInsert(id, realName, score, timeSpent, attempt);
            loadedCount++;
        }

        file.close();
        cout << "[System] Successfully loaded " << loadedCount << " records from " << filename << "!\n";
    }

};
#endif