#include "todo.h"

void TodoList::addTask(const std::string& description) {
    tasks_.push_back(Task(description, false));
};

void TodoList::removeTask(int index) {
    if (index >= 0 && index < tasks_.size()) {
        tasks_.erase(tasks_.begin() + index);
    }
    else {
        std::cerr << "Invalid task index." << std::endl;
    }
};

void TodoList::completeTask(int index) {
    if (index >= 0 && index < tasks_.size()) {
        tasks_[index].setCompleted(true);
    }
    else {
        std::cerr << "Invalid task index." << std::endl;
    }
};

void TodoList::displayTasks() const {
    std::cout << "Tasks:" << std::endl;
    for (int i = 0; i < tasks_.size(); ++i) {
        const Task& task = tasks_[i];
        std::cout << i+1 << ": [" << (task.isCompleted() ? "+" : " ") << "] " << task.getDescription() << std::endl;
    }
    std::cout << std::endl;
};

int TodoList::getTaskCount() const {
    int count = static_cast<int>(tasks_.size());
    return count;
}