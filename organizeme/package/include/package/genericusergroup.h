#pragma once

#include <cinttypes>
#include <string>

class GenericUserGroup {
    public:
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