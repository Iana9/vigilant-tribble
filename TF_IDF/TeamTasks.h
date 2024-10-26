#include <iostream>
#include <string>
#include <map>


#ifndef TEAMTASKS_H
#define TEAMTASKS_H
class TeamTasks
{
public:
    enum struct TaskStatus
    {
        NEW,
        IN_PROGRESS,
        TESTING,
        DONE
    };
    using TasksInfo = std::map<TaskStatus, int>;
    std::map<std::string, TasksInfo> PersonTasks;
    // �������� ���������� �� �������� ����� ����������� ������������
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
        return PersonTasks.at(person);
    }

    // �������� ����� ������ (� ������� NEW) ��� ����������� �������������
    void AddNewTask(const std::string& person) {
        ++PersonTasks[person][TaskStatus::NEW];
    }

    // �������� ������� �� ������� ���������� ����� ����������� ������������,
    // ����������� ��. ����
    std::pair<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
        std::pair<TasksInfo, TasksInfo> taskdiff;
        for (TaskStatus t = TaskStatus::NEW; t != TaskStatus::DONE && task_count > 0; t = static_cast<TaskStatus>(static_cast<int>(t) + 1)) {
            taskdiff.first.insert({ t, 0 });
            taskdiff.second.insert({ t, 0 });
            for (int& tc = PersonTasks[person][t]; tc != 0 && task_count > 0; --tc) {
                --task_count;
                ++PersonTasks[person][static_cast<TaskStatus>(static_cast<int>(t) + 1)];
                ++taskdiff.first[static_cast<TaskStatus>(static_cast<int>(t) + 1)];
            }
            if (taskdiff.first.at(static_cast<TaskStatus>(static_cast<int>(t) + 1)) != 0) {
                taskdiff.second.at(t) = PersonTasks[person][t] - taskdiff.first[t];
            }
        }
        return taskdiff;
    }

    static void PrintTasksInfo(TasksInfo tasks_info) {
       std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
            ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
            ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
            ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
    }
};
#endif TEAMTASKS_H