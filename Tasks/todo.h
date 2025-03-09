#ifndef TO_DO_H
#define TO_DO_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <fstream>

class createDate {
public:
    createDate() {
        time_t now = time(0);
        date_ = ctime(&now);
    }

    std::string getDate() const { return date_; }

private:
    std::string date_;
};

enum DegreeOfImportance {
    LOW,
    MEDIUM,
    HIGH
};

class Task {
public:
    Task(const std::string& description, bool completed = false)
        : description_(description), completed_(completed), degreeOfImportance_(LOW) {
            createDate_ = createDate().getDate();
        }

    std::string getDescription() const { return description_; }
    bool isCompleted() const { return completed_; }
    void setCompleted(bool completed) { completed_ = completed; }
    DegreeOfImportance getDegreeOfImportance() const { return degreeOfImportance_; }
    void setDegreeOfImportance(DegreeOfImportance degree) { degreeOfImportance_ = degree; }
    std::string getCreateDate() const { return createDate_; }
    void setCreateDate(std::string createDate) { createDate_ = createDate; }
private:
    std::string description_;
    bool completed_;
    DegreeOfImportance degreeOfImportance_;
    std::string createDate_;
};

class TodoList {
public:
    void addTask(const std::string& description);
    void removeTask(int index);
    void completeTask(int index);
    void setDegreeOfImportance(int index, DegreeOfImportance degree);
    std::vector<Task> getTasks() const;
    int getTaskCount() const;
    void saveTasks();
    void readHistory();
private:
    std::vector<Task> tasks_;
};

#endif // TO_DO_H