#ifndef _TODO
#define _TODO

#include <string>
#include <vector>
#include <iostream>

class Task {
public:
    Task(const std::string& description, bool completed = false)
        : description_(description), completed_(completed) {}

    std::string getDescription() const { return description_; }
    bool isCompleted() const { return completed_; }
    void setCompleted(bool completed) { completed_ = completed; }

private:
    std::string description_;
    bool completed_;
};

class TodoList {
public:
    void addTask(const std::string& description);
    void removeTask(int index);
    void completeTask(int index);
    void displayTasks() const;
    int getTaskCount() const;

private:
    std::vector<Task> tasks_;
};

#endif // _TODO