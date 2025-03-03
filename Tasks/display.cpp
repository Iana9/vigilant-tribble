#include "display.h"

void Display::print_todo(const std::vector<Task>& container) {
    Display::print_header();
    for (const auto& task : container) {
        Display::print_task(task);
    }
    Display::print_footer();
}

void Display::print_task(const Task& task) {
    fmt::print("[{}] {}: {} - Created date: {}\n", 
        (task.isCompleted()? "X" : " "), 
        task.getDescription().c_str(), 
        task.getDegreeOfImportance() == 0 ? "LOW" : task.getDegreeOfImportance() == 1 ? "MEDIUM" : "HIGH", 
        task.getCreateDate().c_str());
    fmt::print("\n");
}

void Display::print_divider() {
    std::string separator(50, '-');
    fmt::print("{}\n", separator);
}

void Display::print_footer() {
    Display::print_divider();
    fmt::print("\n");
}

void Display::print_header() {
    Display::print_divider();
    fmt::print("TODO List:\n");
    Display::print_divider();
}

void Display::greet_enter(const std::string& message) {
    fmt::print(fg(fmt::color::floral_white) |
    fmt::emphasis::blink, "{}: ", message);
}

void Display::print_exit(const std::string& message) {
    fmt::print(fg(fmt::color::dark_red) |
    fmt::emphasis::italic, "{}\n", message);
}

void Display::print_displayMenu() {
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
    fmt::emphasis::bold, "TODO List Menu:");
    fmt::print("\n");

    std::vector<std::string> menuItems = {
        "Add Task",
        "Remove Task",
        "Complete Task",
        "Increase the priority",
        "Decrease the priority",
        "Display Tasks",
        "Exit"
    };

    for (const auto& item : menuItems) {
        fmt::print(fg(fmt::color::cornflower_blue), 
        "{}. {}\n", (&item - &menuItems[0]) + 1, item);
    }
    fmt::print("\n");
    fmt::print(fg(fmt::color::floral_white) |
    fmt::emphasis::blink, "Enter your choice: ");
}