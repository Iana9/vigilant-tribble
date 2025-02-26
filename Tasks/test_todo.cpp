#include "todo.cpp"

void displayMenu() {
    std::cout << "Todo List Menu:" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. Remove Task" << std::endl;
    std::cout << "3. Complete Task" << std::endl;
    std::cout << "4. Display Tasks" << std::endl;
    std::cout << "5. Exit" << std::endl;
}
int main() {
    TodoList todoList;
    int choice;
    
    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string description;
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                todoList.addTask(description);
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter task index to remove: ";
                std::cin >> index;
                todoList.removeTask(index - 1);
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter task index to complete: ";
                std::cin >> index;
                todoList.completeTask(index - 1);
                break;
            }
            case 4: {
                todoList.displayTasks();
                break;
            }
            case 5: {
                std::cout << "Exiting..." << std::endl;
                return 0;
            }
            default: {
                std::cerr << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    }

    return 0;
}