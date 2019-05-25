#pragma once

#include <cinttypes>
#include <string>
#include <iostream>

#include "genericusergroup.h"

class ChangeUserGroup : public GenericUserGroup {
    public:
        ChangeUserGroup() : GenericUserGroup(0, "", false) {}
        ChangeUserGroup(uint64_t id, std::string groupName, bool isLocal) :
                        GenericUserGroup(id, groupName, isLocal) {}

        void printInfo(){
            std::cout << "Id: " << id << std::endl;
            std::cout << "GroupName: " << groupName << std::endl;
            std::cout << "isLocal: " << isLocal << std::endl; 
        }
};