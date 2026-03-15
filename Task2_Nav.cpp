#include "Task2_Nav.hpp"
#include "Task1_Queue.hpp"
#include "Task3_Log.hpp"

// --- IN-MEMORY ATTEMPT TRACKER ---
static string memoryIDs[100];
static int memoryAttempts[100];
static int memoryCount = 0;

int getStudentAttempts(string id) {
    for(int i = 0; i < memoryCount; i++) {
        if(memoryIDs[i] == id) return memoryAttempts[i];
    }
    return 0; // Starts at 0 every time you open the app!
}

void addStudentAttempt(string id) {
    for(int i = 0; i < memoryCount; i++) {
        if(memoryIDs[i] == id) {
            memoryAttempts[i]++;
            return;
        }
    }
    memoryIDs[memoryCount] = id;
    memoryAttempts[memoryCount] = 1;
    memoryCount++;
}

// --- SessionFlow Implementation ---

SessionFlow::SessionFlow() {
    head = nullptr;
    current = nullptr;
    tail = nullptr;
}

SessionFlow::~SessionFlow() {
    Activity* temp = head;
    while (temp != nullptr) {
        Activity* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}

// Appends a new Activity (Question) to the Doubly Linked List
void SessionFlow::addQuestion(string studentID, string course) {
    Activity* newActivity = new Activity(studentID, course, 0, 0, 1);
    
    if (head == nullptr) {
        head = current = tail = newActivity;
    } else {
        tail->next = newActivity;
        newActivity->prev = tail;
        tail = newActivity;
    }
}

// Sets up the structured sequence of activities
void SessionFlow::buildQuiz(string studentID, string topic) {
    cout << "\n[System] Building " << topic << " Module for " << studentID << "...\n";
    
    // Load 5 questions regardless of the chosen topic
    addQuestion(studentID, topic + " - Q1");
    addQuestion(studentID, topic + " - Q2");
    addQuestion(studentID, topic + " - Q3");
    addQuestion(studentID, topic + " - Q4");
    addQuestion(studentID, topic + " - Q5");
    
    current = head; // Start at the first question
}

void SessionFlow::startSession() {
    if (current == nullptr) return;

    cout << "\n[System] Welcome to the " << current->courseName.substr(0, current->courseName.find(" -")) 
         << " module. Answer all 5 questions to finish. Answers CANNOT be changed.\n";

    while (current != nullptr) {
        cout << "\n=========================================================\n";
        cout << " Topic: " << current->courseName << "\n";
        
        bool isAnswered = (current->timeSpent > 0);
        
        if (isAnswered) {
            cout << " Status: [ COMPLETED - Answer Locked ]\n";
        } else {
            cout << " Status: [ NOT ANSWERED YET ]\n";
        }
        cout << "=========================================================\n";
        
        int correctAnswer = -1;
        
        // --- ARRAYS QUESTIONS ---
        if (current->courseName == "Arrays - Q1") {
            cout << "[Question] In C++, the first element of an array is accessed using the index 1.\n";
            correctAnswer = 0;
        } else if (current->courseName == "Arrays - Q2") {
            cout << "[Question] A standard C++ array cannot change its size once it is declared.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Arrays - Q3") {
            cout << "[Question] The expression myArray[3] accesses the 4th element in the array.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Arrays - Q4") {
            cout << "[Question] Attempting to access an array element outside its bounds will always cause a compile-time error.\n";
            correctAnswer = 0;
        } else if (current->courseName == "Arrays - Q5") {
            cout << "[Question] Arrays in C++ can store a mix of different data types (e.g., integers and strings together).\n";
            correctAnswer = 0;
        }
        // --- LOOPS QUESTIONS ---
        else if (current->courseName == "Loops - Q1") {
            cout << "[Question] A `while` loop checks its condition *before* executing the code block.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Loops - Q2") {
            cout << "[Question] A `do-while` loop is guaranteed to execute its code block at least one time.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Loops - Q3") {
            cout << "[Question] In a `for` loop, the initialization step is executed every single time the loop repeats.\n";
            correctAnswer = 0;
        } else if (current->courseName == "Loops - Q4") {
            cout << "[Question] The `break` statement can be used to exit a loop immediately, even if the condition is still true.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Loops - Q5") {
            cout << "[Question] The `continue` statement completely stops the loop and moves on to the rest of the program.\n";
            correctAnswer = 0;
        }
        // --- POINTERS QUESTIONS ---
        else if (current->courseName == "Pointers - Q1") {
            cout << "[Question] The `&` operator (Address-of operator) is used to find the memory address where a variable is stored.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Pointers - Q2") {
            cout << "[Question] If you have a pointer named `ptr`, typing `*ptr` will output the memory address itself.\n";
            correctAnswer = 0;
        } else if (current->courseName == "Pointers - Q3") {
            cout << "[Question] A pointer variable can be created to store the memory address of another pointer variable.\n";
            correctAnswer = 1;
        } else if (current->courseName == "Pointers - Q4") {
            cout << "[Question] An uninitialized pointer in C++ automatically points to a safe `nullptr` by default.\n";
            correctAnswer = 0;
        } else if (current->courseName == "Pointers - Q5") {
            cout << "[Question] The `new` keyword is used to allocate memory dynamically on the heap, and it returns a pointer to that memory.\n";
            correctAnswer = 1;
        }

        // Hide the answer buttons if they already answered it!
        if (isAnswered) {
            cout << "\nOptions: [2] Move Next   [3] Go Back\n";
        } else {
            cout << "\nOptions: [1] Answer True   [0] Answer False   [2] Move Next   [3] Go Back\n";
        }
        cout << "Choice: ";
        int choice;
        cin >> choice;

        if ((choice == 1 || choice == 0) && !isAnswered) {
            current->timeSpent = 5; // Locks the question!
            
            if (choice == correctAnswer) {
                cout << "\n[System] Correct!\n";
                current->score = 20; 
            } else {
                string correctText = (correctAnswer == 1) ? "True" : "False";
                cout << "\n[System] Incorrect. The correct answer was " << correctText << ".\n";
                current->score = 0;
            }
            
            // Check if all 5 are done
            bool allAnswered = true;
            Activity* scanNode = head;
            while (scanNode != nullptr) {
                if (scanNode->timeSpent == 0) { 
                    allAnswered = false;
                    break;
                }
                scanNode = scanNode->next;
            }

            if (allAnswered) {
                cout << "\n[System] All 5 questions have been answered! Auto-submitting course...\n";
                break; 
            } 
            else if (current->next != nullptr) {
                current = current->next; // Auto-move to next unanswered
            }
        } 
        else if ((choice == 1 || choice == 0) && isAnswered) {
            cout << "\n[Error] Invalid choice. This question is locked.\n";
        }
        else if (choice == 2) {
            if (current->next != nullptr) current = current->next;
            else cout << "[System] You are at the last question.\n";
        } 
        else if (choice == 3) {
            if (current->prev != nullptr) current = current->prev;
            else cout << "[System] You are already at the first question.\n";
        } 
    }
    
    // Process the final grade
    saveToLogQueue();
}

// Deducts the attempt and sends the Final Course Grade to Task 3
void SessionFlow::saveToLogQueue() {
    if (head == nullptr) return;

    string mainTopic = head->courseName.substr(0, head->courseName.find(" -")); 
    string student = head->studentID;

    int totalTime = 0;
    int totalScore = 0;
    int questionsAnswered = 0;

    Activity* temp = head;
    
    while (temp != nullptr) {
        if (temp->timeSpent > 0) {
            totalTime += temp->timeSpent;
            totalScore += temp->score;
            questionsAnswered++;
        }
        temp = temp->next;
    }

    if (questionsAnswered > 0) {
        // --- ADD TO MEMORY INSTEAD OF CSV ---
        addStudentAttempt(student);
        int currentAttempt = getStudentAttempts(student);

        // Send to Task 3 normally (Attempt 1, 2, or 3)
        globalLogQueue.addLog(student, mainTopic, totalTime, totalScore, currentAttempt);
        
        cout << "\n=========================================================\n";
        cout << " COURSE COMPLETED: " << mainTopic << "\n";
        cout << " Final Score: " << totalScore << " / 100\n";
        cout << " Attempt Logged: " << currentAttempt << " / 3\n";
        cout << "=========================================================\n";
        cout << "[Notice] Data sent to Task 3 memory queue.\n";
    }
}

// --- Global Entry Point ---
void runTask2Module() {
    cout << "\n=========================================================\n";
    cout << "          TASK 2: ACTIVITY NAVIGATION & FLOW             \n";
    cout << "=========================================================\n";
    
    cout << "[System] Checking for students currently sitting in the lab...\n";
    globalManager.showStatus(); 

    string id;
    cout << "\n--> Type an Active Student ID from the list above (or type 'exit'): ";
    cin >> id;

    if (id == "exit" || id == "Exit" || id == "EXIT") {
        cout << "[System] Exiting Task 2...\n";
        return;
    }

    if (!globalManager.isStudentActive(id)) {
        cout << "\n[Error] Student '" << id << "' is not at a computer!\n";
        cout << "Hint: Go to Task 1 first, register them, and make sure they have a seat.\n";
        return; 
    }

    // --- READ FROM MEMORY INSTEAD OF CSV ---
    int totalAttempts = getStudentAttempts(id);

    cout << "\n--- Student Profile: " << id << " ---\n";
    cout << " Total System Attempts Used: " << totalAttempts << " / 3\n";
    cout << "----------------------------------\n";

    if (totalAttempts >= 3) {
        cout << "\n[Warning] You have reached the maximum of 3 attempts for the system.\n";
        cout << "[System] Returning to Main Menu...\n";
        return;
    }

    cout << "\nAvailable Topics:\n1. Arrays\n2. Loops\n3. Pointers\nChoice: ";
    int topicChoice;
    cin >> topicChoice;

    string selectedTopic = "Arrays";
    if (topicChoice == 2) selectedTopic = "Loops";
    else if (topicChoice == 3) selectedTopic = "Pointers";

    SessionFlow session;
    session.buildQuiz(id, selectedTopic);
    session.startSession();
}