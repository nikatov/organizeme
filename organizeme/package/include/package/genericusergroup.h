#pragma once

#include <cinttypes>
#include <string>
#include <iostream>
#include <iomanip>

class GenericUserGroup {
    public:
        void printInfo(){
            std::cout << "id: " << std::setw(6) << id << " | ";
            std::cout << "groupName: " << std::setw(16) << groupName << " | ";
            std::cout << "isLocal: " << std::setw(5) << (isLocal ? "true" : "false") << " |" << std::endl;
        }
        uint64_t getId() { return id; }
        std::string getGroupName() { return groupName; }
        bool getIsLocal() { return isLocal; }

        void setId(uint64_t id) { this->id = id; }
        void setGroupName(std::string groupName) { this->groupName = groupName; }
        void setIsLocal(bool isLocal) { this->isLocal = isLocal; }
    protected:
        GenericUserGroup(uint64_t id, std::string groupName, bool isLocal) :
                        id(id), groupName(groupName), isLocal(isLocal) {}

        uint64_t id;
        std::string groupName;
        bool isLocal;
};