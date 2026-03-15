#include <iostream>
#include <string>
#include "Student.hpp"

// --- ALL MODULE INCLUDES ---
#include "Task1_Queue.hpp"
#include "Task2_Nav.hpp"      // <-- Uncommented your Task 2!
#include "Task3_Log.hpp"
#include "Task4_Priority.hpp"

using namespace std;

void displayMenu() {
    cout << "\n========================================================\n";
    cout << "   APU PLAPS: Programming Learning Analytics System     \n";
    cout << "========================================================\n";
    cout << "1. Learner Registration & Session (Task 1)\n";
    cout << "2. Activity Navigation & Flow (Task 2)\n";
    cout << "3. Recent Activity Logging (Task 3)\n";
    cout << "4. At-Risk Learner Priority (Task 4)\n";
    cout << "5. Exit System\n";
    cout << "--------------------------------------------------------\n";
    cout << "Enter your choice (1-5): ";
}

int main() {
    int choice = 0;

    // The main system loop
    while (choice != 5) {
        displayMenu();
        cin >> choice;

        // Clear the input buffer just in case the user types a letter by accident
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0; 
        }

        cout << "\n";

        switch (choice) {
            case 1:
                cout << "[System] Launching Task 1 Module...\n";
                runTask1Module(); // <-- Added Task 1 launch!
                cout << "\n[System] Exiting Task 1 Module. Press Enter to return to main menu.\n";
                cin.ignore(10000, '\n'); 
                cin.get();
                break;
            case 2:
                cout << "[System] Launching Task 2 Module...\n";
                runTask2Module(); // <-- Added your Task 2 launch!
                cout << "\n[System] Exiting Task 2 Module. Press Enter to return to main menu.\n";
                cin.ignore(10000, '\n'); 
                cin.get();
                break;
            case 3:
                cout << "[System] Launching Task 3 Module...\n";
                runTask3Module(); 
                cout << "\n[System] Exiting Task 3 Module. Press Enter to return to main menu.\n";
                cin.ignore(10000, '\n'); 
                cin.get();
                break;
            case 4:{
                cout << "[System] Launching Task 4 Module...\n";
                
                // 1. Create your Priority Queue object
                AtRiskPriorityQueue riskQueue;

                cout << "[System] Analyzing recent activity logs (Simulation)...\n";

                // 2. Read the actual logs.csv file directly
                riskQueue.loadFromLogsCSV("logs.csv");

                // 3. Display the sorted list to the console
                riskQueue.displayQueue();

                // 4. Export the result to CSV as required by Assignment
                riskQueue.exportToCSV();

                cout << "\n[System] Task 4 Module executed successfully. Press Enter to return to menu.\n";
                cin.ignore(); 
                cin.get();
                break;
            }
            case 5:
                cout << "[System] Shutting down PLAPS... Goodbye!\n";
                break;
            default:
                cout << "[Error] Invalid input. Please select a number from 1 to 5.\n";
        }
    }

    return 0;
}