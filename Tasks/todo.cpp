#include "todo.h"

void TodoList::addTask(const std::string& description) {
    tasks_.push_back(Task(description, false));
}

void TodoList::removeTask(int index) {
    if (index >= 0 && index < tasks_.size()) {
        tasks_.erase(tasks_.begin() + index);
    }
    else {
        std::cerr << "Invalid task index." << std::endl;
    }
}

void TodoList::completeTask(int index) {
    if (index >= 0 && index < static_cast<int>(tasks_.size())) {
        tasks_[index].setCompleted(true);
    }
    else {
        std::cerr << "Invalid task index." << std::endl;
    }
}

void TodoList::setDegreeOfImportance(int index, DegreeOfImportance degree) {
    if (index >= 0 && index < tasks_.size()) {
        tasks_[index].setDegreeOfImportance(degree);
    }
    else {
        std::cerr << "Invalid task index." << std::endl;
    }
}

std::vector<Task> TodoList::getTasks() const {
    return tasks_;
}

int TodoList::getTaskCount() const {
    int count = static_cast<int>(tasks_.size());
    return count;
}