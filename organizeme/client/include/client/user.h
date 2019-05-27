#pragma once

#include <vector>

#include "usergroup.h"
#include "package/genericuser.h"
#include "package/changeusergroup.h"

class User : public GenericUser {
    public:
        User(uint64_t id, std::string username, std::string lastName, std::string firstName,
            std::string patronymic, std::string password) :
            GenericUser(id, username, lastName, firstName, patronymic, password) {};
        
        ~User(){
            for(auto ug : userGroups){
                delete ug;
            }
        }

        std::vector<UserGroup*> getUserGroups() { return userGroups; }
        void addUserGroup(UserGroup *userGroup);
        std::unique_ptr<ChangeUserGroup> changeUserGroup(std::unique_ptr<ChangeUserGroup> changeUserGroup);
        void deleteUserGroup(uint64_t idUserGroup);
        void printUserGroups();
    private:
        std::vector<UserGroup*> userGroups;
};