#pragma once

#include <cinttypes>
#include <string>
#include <iostream>
#include <iomanip>

class GenericTaskGroup {
    public:
        uint64_t getId() { return id; }
        std::string getName() { return name; }

        void setId(uint64_t id) { this->id = id; }
        void setName(std::string name) { this->name = name; }
        void printInfo(){
            std::cout << "Id: " << std::setw(6) << id << std::endl;
            std::cout << "Name: " << std::setw(16) << name << std::endl;
        }
    protected:
        GenericTaskGroup(uint64_t id, std::string name) : id(id), name(name) {}

        uint64_t id;
        std::string name;
};