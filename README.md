# PLAPS


struct Student 
    string studentID;
    string name;
    int riskScore;         // Used by Task 4 (Priority Queue)
    int currentActivityID; // Used by Task 2 & 3

# logs.csv
The Required Columns:
    LogID (To track the attempt)
    StudentID (Who did the activity)
    Topic (What they studied, e.g., "Pointers")
    Difficulty (e.g., "Easy", "Medium", "Hard")
    Score (Their result)

Example CSV Row: LOG001, TP123456, Pointers, Hard, 45

# at_risk_students.csv
The Required Columns:
    StudentID
    Name
    RiskScore (The calculated number showing how much they are struggling) 
    RecommendedAction (e.g., "Repeat topic" or "Attempt easier activity") 

Example CSV Row: TP123456, Ali, 88, Repeat Pointers module

# students.csv
StudentID,Name,RiskScore,TotalTimeSpent,TotalFailedAttempts