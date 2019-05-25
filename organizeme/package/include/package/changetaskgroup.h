#pragma once

#include <cinttypes>
#include <string>
#include <iostream>

#include "generictaskgroup.h"

class ChangeTaskGroup : public GenericTaskGroup {
    public:
        ChangeTaskGroup() : GenericTaskGroup(0, ""), idUserGroup() {}
        ChangeTaskGroup(int64_t id, int64_t idUserGroup, std::string name) : 
                        GenericTaskGroup(id, name), idUserGroup(idUserGroup) {}

        void printInfo(){
            std::cout << "Id: " << id << std::endl;
            std::cout << "IdUserGroup: " << idUserGroup << std::endl;
            std::cout << "Name: " << name << std::endl;
        }

        uint64_t getIdUserGroup() { return idUserGroup; }

        void setIdUserGroup(int64_t idUserGroup) { this->idUserGroup = idUserGroup; }
    private:
        uint64_t idUserGroup;
};