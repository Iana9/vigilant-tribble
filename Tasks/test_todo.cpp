#include "todo.h"
#include "display.h"

int getChoice() {
    int choice;
    while (true) {
        Display::print_displayMenu();
        std::cin >> choice;

        if (choice < MenuOption::ADD_TASK || choice > MenuOption::EXIT) {
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid choice. Please try again." << std::endl;
        } else {
            std::cin.ignore(); // Игнорируем оставшийся символ новой строки
            return choice;
        }
    }
}

void handle_AddTask(TodoList& todoList) {
    std::string description;
    Display::greet_enter("Enter task description");
    std::getline(std::cin, description);
    todoList.addTask(description);
}

void handle_RemoveTask(TodoList& todoList) {
    int index;
    Display::greet_enter("Enter task index to remove");
    std::cin >> index;
    todoList.removeTask(index - 1);
}

void handle_CompleteTask(TodoList& todoList) {
    int index;
    Display::greet_enter("Enter task index to complete");
    std::cin >> index;
    todoList.completeTask(index - 1);
}

void handle_DisplayTasks(const TodoList& todoList) {
    Display::print_todo(todoList.getTasks());
}

void handle_IncreasePriority(TodoList& todoList) {
    int index;
    Display::greet_enter("Enter task index to increase the priority");
    std::cin >> index;
    Task& task = todoList.getTasks()[index - 1];
    DegreeOfImportance currentImportance = task.getDegreeOfImportance();

    if (currentImportance < HIGH) {
        todoList.setDegreeOfImportance(index - 1, static_cast<DegreeOfImportance>(currentImportance + 1));
        std::cout << "Priority increased." << std::endl;
    } else {
        std::cout << "Task already has the highest priority." << std::endl;
    }
}

void handle_DecreasePriority(TodoList& todoList) {
    int index;
    Display::greet_enter("Enter task index to decrease the priority");
    std::cin >> index;
    Task& task = todoList.getTasks()[index - 1];
    DegreeOfImportance currentImportance = task.getDegreeOfImportance();

    if (currentImportance > LOW) {
        todoList.setDegreeOfImportance(index - 1, static_cast<DegreeOfImportance>(currentImportance - 1));
        std::cout << "Priority increased." << std::endl;
    } else {
        std::cout << "Task already has the highest priority." << std::endl;
    }
}

void handle_Exit(TodoList& todoList) {
    todoList.saveTasks();
    Display::print_exit("Exiting...");
}

bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void handle_History(TodoList& todoList) {
    const char* history = "todo_list_history.json";
    if (file_exists(history)) {
        std::string choice;
        Display::greet_enter("There exists the previous session of tasks. Do you want to load them? Enter y/n");
        std::cin >> choice;
        if (choice == "y" || choice == "Y") {
            todoList.readHistory();
        }
    }
}

int main() {
    TodoList todoList;
    int choice;
    handle_History(todoList);

    while (true) {
        choice = getChoice();

        switch (choice) {
            case MenuOption::ADD_TASK: {
                handle_AddTask(todoList);
                break;
            }
            case MenuOption::REMOVE_TASK: {
                handle_RemoveTask(todoList);
                break;
            }
            case MenuOption::COMPLETE_TASK: {
                handle_CompleteTask(todoList);
                break;
            }
            case MenuOption::INCREASE_THE_PRIORITY: {
                handle_IncreasePriority(todoList);
                break;
            }
            case MenuOption::DECREASE_THE_PRIORITY: {
                handle_DecreasePriority(todoList);
                break;
            }
            case MenuOption::DISPLAY_TASKS: {
                handle_DisplayTasks(todoList);
                break;
            }
            case MenuOption::EXIT: {
                handle_Exit(todoList);
                return 0;
            }
        }
    }
}