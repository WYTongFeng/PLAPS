#include "Task4_Priority.hpp"

// Constructor
AtRiskPriorityQueue::AtRiskPriorityQueue() {
    head = nullptr;
}

// Function 1
void AtRiskPriorityQueue::analyzeAndInsert(string id, string name, int score, int timeSpent, int attempt) {
    int calculatedRisk = 0;
    string rec = ""; 

    if (score < 40) {
        calculatedRisk += 50;
        rec += "[Urgent: Repeat the entire topic immediately.] ";
    } else if (score < 60) {
        calculatedRisk += 30;
        rec += "[Review the study materials and try an easier activity.] ";
    }

    if (attempt >= 3) {
        calculatedRisk += 20;
        rec += "[Please consult the lecturer for 1-to-1 help.] ";
    }

    if (timeSpent > 60 && score < 50) {
        calculatedRisk += 10;
        // Risk score increases, but no extra nagging text needed
    }

    if (calculatedRisk == 0) {
        rec = "Keep up the good work!";
    }

    enqueue(id, name, calculatedRisk, rec);
}

// Function 2
void AtRiskPriorityQueue::enqueue(string id, string name, int risk, string rec) {
    Student* current = head;
    Student* previous = nullptr;
    
    int totalRisk = risk; 
    string finalRec = rec;

    // SMART TEXT FILTER: Must match the exact phrases above so they don't repeat!
    string warnings[] = {
        "[Urgent: Repeat the entire topic immediately.] ", 
        "[Review the study materials and try an easier activity.] ", 
        "[Please consult the lecturer for 1-to-1 help.] "
    };

    while (current != nullptr) {
        if (current->studentID == id) {
            totalRisk += current->riskScore;
            
            finalRec = current->recommendation;
            if (finalRec == "Keep up the good work!") finalRec = ""; 

            for(string w : warnings) {
                if (rec.find(w) != string::npos && finalRec.find(w) == string::npos) {
                    finalRec += w;
                }
            }
            if (finalRec.empty()) finalRec = "Keep up the good work!";

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

    Student* newStudent = new Student(id, name, totalRisk, finalRec);

    if (head == nullptr || totalRisk > head->riskScore) {
        newStudent->next = head;
        head = newStudent;
    } else {
        current = head;
        while (current->next != nullptr && current->next->riskScore >= totalRisk) {
            current = current->next;
        }
        newStudent->next = current->next;
        current->next = newStudent;
    }
}

// Function 3
void AtRiskPriorityQueue::displayQueue() {
    if (head == nullptr) {
        cout << "No at-risk students currently.\n";
        return;
    }

    cout << "\n=== At-Risk Learners Priority List ===\n";
    Student* current = head;
    int rank = 1;

    while (current != nullptr) {
        cout << rank << ". [" << current->studentID << "] " << current->name 
             << " | Risk Score: " << current->riskScore << "\n"
             << "   Recommendation: " << current->recommendation << "\n";
        
        current = current->next;
        rank++;
    }
    cout << "======================================\n";
}

// Function 4
void AtRiskPriorityQueue::exportToCSV() {
    ofstream outFile("at_risk_students.csv");
    if (!outFile) {
        cout << "[Error] Error opening file for writing!\n";
        return;
    }

    outFile << "StudentID,RiskScore,Recommendation\n";

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

// Function 5
string AtRiskPriorityQueue::getStudentNameFromCSV(string searchID) {
    ifstream studentFile("student.csv");
    if (!studentFile.is_open()) return "Learner"; 

    string line;
    getline(studentFile, line); 

    while (getline(studentFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name;
        
        getline(ss, id, ',');
        getline(ss, name, ',');

        id.erase(0, id.find_first_not_of(" \r\n\t"));
        id.erase(id.find_last_not_of(" \r\n\t") + 1);
        searchID.erase(0, searchID.find_first_not_of(" \r\n\t"));
        searchID.erase(searchID.find_last_not_of(" \r\n\t") + 1);

        if (id == searchID) {
            name.erase(0, name.find_first_not_of(" \r\n\t"));
            studentFile.close();
            return name; 
        }
    }
    studentFile.close();
    return "Unknown"; 
}

// Function 6
void AtRiskPriorityQueue::loadFromLogsCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[Error] Could not open " << filename << "!\n";
        return;
    }

    string line;
    getline(file, line); 
    int loadedCount = 0;

    while (getline(file, line)) {
        if (line.empty()) continue; 

        stringstream ss(line);
        string id, course, timeStr, scoreStr, attemptStr;

        getline(ss, id, ',');
        getline(ss, course, ',');
        getline(ss, timeStr, ',');
        getline(ss, scoreStr, ',');
        getline(ss, attemptStr, ',');

        int timeSpent = stoi(timeStr);
        int score = stoi(scoreStr);
        int attempt = stoi(attemptStr);

        string realName = getStudentNameFromCSV(id);
        analyzeAndInsert(id, realName, score, timeSpent, attempt);
        loadedCount++;
    }

    file.close();
    cout << "[System] Successfully loaded " << loadedCount << " records from " << filename << "!\n";
}

// Function 7
void AtRiskPriorityQueue::clearQueue() {
    Student* current = head;
    while (current != nullptr) {
        Student* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

// Menu Function
void runTask4Module() {
    AtRiskPriorityQueue riskQueue;
    int choice = 0;
    bool dataLoaded = false;

    while (true) {
        cout << "\n--- Task 4: At-Risk Priority Engine Menu ---\n";
        cout << "1. Process Activity Logs (Load logs.csv)\n";
        cout << "2. Display Priority List\n";
        cout << "3. Export to at_risk_students.csv\n";
        cout << "4. Return to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            riskQueue.clearQueue(); 
            cout << "\n[System] Analyzing recent activity logs...\n";
            riskQueue.loadFromLogsCSV("logs.csv");
            dataLoaded = true;
        } else if (choice == 2) {
            if (!dataLoaded) cout << "\n[Warning] You must process the logs (Option 1) first!\n";
            else riskQueue.displayQueue();
        } else if (choice == 3) {
            if (!dataLoaded) cout << "\n[Warning] You must process the logs (Option 1) first!\n";
            else riskQueue.exportToCSV();
        } else if (choice == 4) {
            break;
        } else {
            cout << "\n[Error] Invalid choice.\n";
        }
    }
}