#pragma once

#include <vector>

#include "task.h"
#include "package/generictaskgroup.h"
#include "package/changetask.h"

class UserGroup;

class TaskGroup : public GenericTaskGroup{
    public:
        TaskGroup(uint64_t id, UserGroup *userGroup, std::string name) :
                  GenericTaskGroup(id, name), userGroup(userGroup) {}

        void addTask(Task *task);
        void changeTask(ChangeTask *changeTask);
        void deleteTask(uint64_t idTask);
        void printTasks();
    private:
        UserGroup *userGroup;
        std::vector<Task*> tasks;
};