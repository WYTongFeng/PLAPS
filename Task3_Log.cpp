#include "Task3_Log.hpp"

// Constructor initializes the circular queue
ActivityLogQueue::ActivityLogQueue(int size) {
    capacity = size;
    logArray = new Activity[capacity];
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor cleans up the dynamically allocated array
ActivityLogQueue::~ActivityLogQueue() {
    delete[] logArray;
}

// Records a new activity log, overwrites the oldest record when full (O(1) time complexity)
void ActivityLogQueue::addLog(string id, string course, int time, int score, int attempt) {
    // Circularly move the rear pointer
    rear = (rear + 1) % capacity; 
    
    // Insert data at the new rear position
    logArray[rear].studentID = id;
    logArray[rear].courseName = course;
    logArray[rear].timeSpent = time;
    logArray[rear].score = score;
    logArray[rear].attemptNumber = attempt;

    if (count < capacity) {
        count++; // Queue is not full yet, increment the total count
    } else {
        // If the queue is full, the oldest record is overwritten by the new rear.
        // Therefore, the front pointer must move forward to point to the new "oldest" record.
        front = (front + 1) % capacity; 
    }
}

// Displays all currently stored activity logs
void ActivityLogQueue::displayAllLogs() {
    if (count == 0) {
        cout << "[System] The activity log is currently empty.\n";
        return;
    }

    cout << "\n=== Recent Activity Logs ===\n";
    int current = front; // Start from the oldest record
    for (int i = 0; i < count; i++) {
        cout << "[" << logArray[current].studentID << "] "
             << "Course: " << logArray[current].courseName << " | "
             << "Score: " << logArray[current].score << " | "
             << "Time: " << logArray[current].timeSpent << "m | "
             << "Attempt: " << logArray[current].attemptNumber << "\n";
        
        // Circularly move to the next record
        current = (current + 1) % capacity;
    }
    cout << "----------------------------\n";
}

// Filters and displays logs for a specific student ID
void ActivityLogQueue::filterLogsByStudent(string targetID) {
    if (count == 0) {
        cout << "[System] The activity log is currently empty.\n";
        return;
    }

    cout << "\n=== Activity Logs for Student: " << targetID << " ===\n";
    int current = front;
    bool found = false;
    
    // Traverse the queue starting from the front
    for (int i = 0; i < count; i++) {
        if (logArray[current].studentID == targetID) {
            cout << "Course: " << logArray[current].courseName << " | "
                 << "Score: " << logArray[current].score << " | "
                 << "Time: " << logArray[current].timeSpent << "m | "
                 << "Attempt: " << logArray[current].attemptNumber << "\n";
            found = true;
        }
        current = (current + 1) % capacity;
    }

    if (!found) {
        cout << "No activity records found for this student.\n";
    }
    cout << "-------------------------------------------\n";
}

// Exports all current logs to a structured CSV format for analysis
void ActivityLogQueue::exportToCSV(string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "[Error] Could not open file for writing: " << filename << "\n";
        return;
    }

    // Write the CSV header row
    outFile << "StudentID,CourseName,TimeSpent,Score,AttemptNumber\n";

    int current = front;
    for (int i = 0; i < count; i++) {
        outFile << logArray[current].studentID << ","
                << logArray[current].courseName << ","
                << logArray[current].timeSpent << ","
                << logArray[current].score << ","
                << logArray[current].attemptNumber << "\n";
        
        current = (current + 1) % capacity;
    }

    outFile.close();
    cout << "[System] Activity logs successfully exported to " << filename << "\n";
}

// --- NEW: Create the shared global queue here ---
ActivityLogQueue globalLogQueue(50);

// Global entry point function to be called by main.cpp menu
void runTask3Module() {

    int choice = 0;

    while (true) {
        cout << "\n--- Task 3: Activity Logging Menu ---\n";
        cout << "1. Simulate New Activity Entry\n";
        cout << "2. View All Activity Logs\n";
        cout << "3. Filter Logs by Student ID\n";
        cout << "4. Export Logs to CSV\n";
        cout << "5. Return to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string id, course;
            int time, score, attempt;
            cout << "Student ID: "; cin >> id;
            cout << "Course Name: "; cin >> course;
            cout << "Time Spent (mins): "; cin >> time;
            cout << "Score (0-100): "; cin >> score;
            cout << "Attempt Number: "; cin >> attempt;
            
            // Use globalLogQueue!
            globalLogQueue.addLog(id, course, time, score, attempt);
            cout << "[System] Log added successfully.\n";
        } else if (choice == 2) {
            // Use globalLogQueue!
            globalLogQueue.displayAllLogs();
        } else if (choice == 3) {
            string target;
            cout << "Enter Student ID to filter: ";
            cin >> target;
            globalLogQueue.filterLogsByStudent(target);
        } else if (choice == 4) {
            // Use globalLogQueue AND export to the correct file!
            globalLogQueue.exportToCSV("logs.csv");
        } else if (choice == 5) {
            break; 
        } else {
            cout << "[Error] Invalid choice.\n";
        }
    }
}