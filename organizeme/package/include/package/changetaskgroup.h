#pragma once

#include <cinttypes>
#include <string>
#include <iostream>

class ChangeTaskGroup {
    public:
        ChangeTaskGroup() : id(-1), idUserGroup(-1), name("") {}
        ChangeTaskGroup(int64_t id, int64_t idUserGroup, std::string name) : 
                            id(id), idUserGroup(idUserGroup), name(name) {}

        void printInfo(){
            std::cout << "Id: " << id << std::endl;
            std::cout << "IdUserGroup: " << idUserGroup << std::endl;
            std::cout << "Name: " << name << std::endl;
        }

        int64_t getId() { return id; }
        int64_t getIdUserGroup() { return idUserGroup; }
        std::string getName() { return name; }

        void setId(int64_t id) { this->id = id; }
        void setIdUserGroup(int64_t idUserGroup) { this->idUserGroup = idUserGroup; }
        void setName(std::string name) { this->name = name; }
    private:
        int64_t id;
        int64_t idUserGroup;
        std::string name;
};