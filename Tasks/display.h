#ifndef DISPLAY_H
#define DISPLAY_H

#include <fmt/color.h>
#include <fmt/core.h>
#include <iostream>
#include <vector>
#include <string>
#include "todo.h"

enum MenuOption {
    ADD_TASK = 1,
    REMOVE_TASK,
    COMPLETE_TASK,
    INCREASE_THE_PRIORITY,
    DECREASE_THE_PRIORITY,
    DISPLAY_TASKS,
    EXIT
};

class Display {
    public:
    static void print_todo(const std::vector<Task>& container);
    static void print_task(const Task& task);
    static void print_divider();
    static void print_footer();
    static void print_header();
    static void print_displayMenu();
    static void greet_enter(const std::string& message);
    static void print_exit(const std::string& message);
};

#endif // DISPLAY_H