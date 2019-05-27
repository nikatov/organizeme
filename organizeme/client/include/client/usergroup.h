#pragma once

#include <cinttypes>
#include <string>

#include "taskgroup.h"
#include "package/changetaskgroup.h"
#include "package/genericusergroup.h"

class User;

class UserGroup : public GenericUserGroup {
    public:
        UserGroup(uint64_t id, std::string groupName, bool isLocal) : GenericUserGroup(id, groupName, isLocal) {}

        ~UserGroup(){
            for(auto tg : taskGroups){
                delete tg;
            }
        }

        User* getUser() { return user; }
        void addTaskGroup(TaskGroup *taskGroup);
        void changeTaskGroup(ChangeTaskGroup *changeTaskGroup);
        void deleteTaskGroup(uint64_t idTaskGroup);
        void printTaskGroups();
    private:
        User *user;
        std::vector<TaskGroup*> taskGroups;
};