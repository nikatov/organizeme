#pragma once

#include <cinttypes>
#include <string>

class GenericTaskGroup {
    public:
        uint64_t getId() { return id; }
        std::string getName() { return name; }

        void setId(uint64_t id) { this->id = id; }
        void setName(std::string name) { this->name = name; }
    protected:
        GenericTaskGroup(uint64_t id, std::string name) : id(id), name(name) {}

        uint64_t id;
        std::string name;
};