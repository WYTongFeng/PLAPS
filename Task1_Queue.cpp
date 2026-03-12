#include "Task1_Queue.hpp"
#include <fstream>
#include <sstream>

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
    cout << "\n--- PLAPS Task 1 Status (3 Capacity) ---" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Slot " << i + 1 << ": " << (slotOccupied[i] ? activeSession[i]->name : "[Available]") << endl;
    }
    waitingQueue.display();
    cout << "----------------------------------------\n" << endl;
}

// --- 全局入口 ---
void runTask1Module() {
    static Task1Manager manager;
    int choice;
    while (true) {
        cout << "1. Manual Register\n2. Load from student.csv\n3. Exit Session\n4. Show Status\n5. Back\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            string id, name;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            manager.registerLearner(id, name);
        } else if (choice == 2) {
            manager.loadFromCSV();
        } else if (choice == 3) {
            int s; cout << "Slot (1-3): "; cin >> s;
            manager.logoutLearner(s);
        } else if (choice == 4) {
            manager.showStatus();
        } else break;
    }
}