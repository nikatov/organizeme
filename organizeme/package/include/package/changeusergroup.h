#pragma once

#include <cinttypes>
#include <string>
#include <iostream>

class ChangeUserGroup {
    public:
        ChangeUserGroup() : id(-1), groupName(""), isLocal(false) {}
        ChangeUserGroup(uint64_t id, std::string groupName, bool isLocal) : id(id),
                                             groupName(groupName), isLocal(isLocal) {}

        void printInfo(){
            std::cout << "Id: " << id << std::endl;
            std::cout << "GroupName: " << groupName << std::endl;
            std::cout << "isLocal: " << isLocal << std::endl; 
        }

        uint64_t getId() { return id; }
        std::string getGroupName() { return groupName; }
        bool getIsLocal() { return isLocal; }

        void setId(uint64_t id) { this->id = id; }
        void setGroupName(std::string groupName) { this->groupName = groupName; }
        void setIsLocal(bool isLocal) { this->isLocal = isLocal; }
    private:
        uint64_t id;
        std::string groupName;
        bool isLocal;
};