#include "Task1_Queue.hpp"
#include <fstream>
#include <sstream>

// --- NEW: Create the actual global manager here ---
Task1Manager globalManager;

// --- RegistrationQueue 实现 ---
RegistrationQueue::RegistrationQueue() : front(nullptr), rear(nullptr) {}

void RegistrationQueue::enqueue(string id, string name) {
    StudentNode* newNode = new StudentNode(id, name);
    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

StudentNode* RegistrationQueue::dequeue() {
    if (front == nullptr) return nullptr;
    StudentNode* temp = front;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    return temp;
}

bool RegistrationQueue::isEmpty() { return front == nullptr; }

void RegistrationQueue::display() {
    if (isEmpty()) {
        cout << "Waiting Queue: [Empty]" << endl;
        return;
    }
    StudentNode* curr = front;
    cout << "Waiting Queue: ";
    while (curr) {
        cout << curr->name << " -> ";
        curr = curr->next;
    }
    cout << "END" << endl;
}

// --- Task1Manager 实现 ---
Task1Manager::Task1Manager() {
    for (int i = 0; i < 3; i++) {
        activeSession[i] = nullptr;
        slotOccupied[i] = false;
    }
}

void Task1Manager::loadFromCSV() {
    ifstream file("student.csv");
    if (!file.is_open()) {
        cout << "[Error] Could not open student.csv" << endl;
        return;
    }
    string line, id, name;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        registerLearner(id, name);
    }
    file.close();
    cout << "[System] Data loaded from student.csv" << endl;
}

void Task1Manager::registerLearner(string id, string name) {
    waitingQueue.enqueue(id, name);
    autoFillSession();
}

void Task1Manager::autoFillSession() {
    for (int i = 0; i < 3; i++) {
        if (!slotOccupied[i] && !waitingQueue.isEmpty()) {
            activeSession[i] = waitingQueue.dequeue();
            slotOccupied[i] = true;
            cout << "[Task 1] " << activeSession[i]->name << " enters Slot " << i+1 << endl;
        }
    }
}

void Task1Manager::logoutLearner(int slot) {
    int idx = slot - 1;
    if (idx >= 0 && idx < 3 && slotOccupied[idx]) {
        cout << "[Task 1] " << activeSession[idx]->name << " left Slot " << slot << endl;
        delete activeSession[idx];
        activeSession[idx] = nullptr;
        slotOccupied[idx] = false;
        autoFillSession(); 
    } else {
        cout << "[Error] Invalid Slot." << endl;
    }
}

void Task1Manager::showStatus() {
    cout << "\n--- PLAPS Task 1 Status (3 Capacity) ---\n";
    for (int i = 0; i < 3; i++) {
        if (slotOccupied[i] && activeSession[i] != nullptr) {
            // Uses ->studentID and ->name to match your .hpp exactly!
            cout << "Slot " << i + 1 << ": [" << activeSession[i]->studentID << "] " << activeSession[i]->name << "\n";
        } else {
            cout << "Slot " << i + 1 << ": [EMPTY]\n";
        }
    }
    // Uses .display() to match your .hpp exactly!
    waitingQueue.display(); 
    cout << "----------------------------------------\n";
}

// --- NEW: The security check logic ---
bool Task1Manager::isStudentActive(string id) {
    for (int i = 0; i < 3; i++) {
        // If the slot is taken AND the ID matches the student sitting there
        if (slotOccupied[i] && activeSession[i] != nullptr && activeSession[i]->studentID == id) {
            return true; // Access Granted!
        }
    }
    return false; // Access Denied! They are not in the lab.
}

// --- 全局入口 ---
void runTask1Module() {
    // REMOVE THIS LINE: static Task1Manager manager;
    int choice;
    while (true) {
            cout << "1. Manual Register\n2. Load from student.csv\n3. Exit Session\n4. Show Status\n5. Back\nChoice: ";
            cin >> choice;
            if (choice == 1) {
                string id, name;
                cout << "ID: "; cin >> id;
                cout << "Name: "; cin.ignore(); getline(cin, name);
                globalManager.registerLearner(id, name); // Changed to globalManager
            } else if (choice == 2) {
                globalManager.loadFromCSV(); // Changed to globalManager
            } else if (choice == 3) {
                int s; cout << "Slot (1-3): "; cin >> s;
                globalManager.logoutLearner(s); // Changed to globalManager
            } else if (choice == 4) {
                globalManager.showStatus(); // Changed to globalManager
            } else break;
        }
}