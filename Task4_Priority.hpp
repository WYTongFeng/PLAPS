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
    void analyzeAndInsert(string id, string name, int score, int timeSpent, int attempt) {
        int calculatedRisk = 0;
        string rec = ""; // Start blank so we can combine them!

        // Rule 1: Low score adds high risk
        if (score < 40) {
            calculatedRisk += 50;
            rec += "[Urgent: Topic failed. ] ";
        } else if (score < 60) {
            calculatedRisk += 30;
            rec += "[Review materials. ] ";
        }

        // Rule 2: Too many attempts means they are stuck
        if (attempt >= 3) {
            calculatedRisk += 20;
            rec += "[Max attempts reached - Consult Lecturer. ] ";
        }

        // Rule 3: Spending too much time but getting low score
        if (timeSpent > 60 && score < 50) {
            calculatedRisk += 10;
            rec += "[Struggling with time limit. ] ";
        }

        // If they did perfectly fine, give them the default message
        if (calculatedRisk == 0) {
            rec = "Keep up the good work!";
        }

        // Send to enqueue (which will now handle duplicates perfectly)
        enqueue(id, name, calculatedRisk, rec);
    }

    // ---------------------------------------------------------
    // Function 2: Insert into Priority Queue (SMART MERGE VERSION)
    // ---------------------------------------------------------
    void enqueue(string id, string name, int risk, string rec) {
        // STEP 1: Check if this student is ALREADY in the priority queue
        Student* current = head;
        Student* previous = nullptr;
        
        int totalRisk = risk; 
        string finalRec = rec;

        while (current != nullptr) {
            if (current->studentID == id) {
                // We found a duplicate! Add the old risk and the new risk together
                totalRisk += current->riskScore;
                
                // Combine the recommendations if they aren't default
                if (current->recommendation != "Keep up the good work!" && rec != "Keep up the good work!") {
                    finalRec = current->recommendation + rec;
                } else if (rec == "Keep up the good work!") {
                    finalRec = current->recommendation; // Keep the warning!
                }

                // REMOVE the old node temporarily so we can re-insert them in their new sorted position
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                break;
            }
            previous = current;
            current = current->next;
        }

        // STEP 2: Create the new updated student node
        Student* newStudent = new Student(id, name, totalRisk, finalRec);

        // STEP 3: Insert them back into the queue based on their NEW TOTAL risk score
        if (head == nullptr || totalRisk > head->riskScore) {
            // Put at the very front
            newStudent->next = head;
            head = newStudent;
        } else {
            current = head;
            // Find the correct spot
            while (current->next != nullptr && current->next->riskScore >= totalRisk) {
                current = current->next;
            }
            // Insert
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