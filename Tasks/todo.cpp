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

void TodoList::readHistory() {
    const char* history = "todo_list_history.json";
    using json = nlohmann::json;
    std::ifstream infile(history);
    json data = json::parse(infile);
    for (auto& task : data) {
        Task tsk(task["description"], task["completed"]);
        tsk.setCompleted(task["completed"]);
        tsk.setDegreeOfImportance(task["degreeOfImportance"]);
        tsk.setCreateDate(task["createDate"]);
        this->tasks_.push_back(tsk);
    }
}

void TodoList::saveTasks() {
    using json = nlohmann::json;
    json j;
    json tmp_json;
    std::ofstream outfile("todo_list_history.json", std::ios::app);
    for (int i = 0; i < tasks_.size(); i++) {
        Task& task = tasks_[i];
        tmp_json = {
            {"description", task.getDescription()},
            {"completed", task.isCompleted()},
            {"degreeOfImportance", task.getDegreeOfImportance()},
            {"createDate", task.getCreateDate()}
        };
        j[fmt::format("{}", i)] = tmp_json;
    }
    outfile << j;
    outfile.close();
}