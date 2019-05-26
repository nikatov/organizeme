#pragma once

#include <cinttypes>
#include <string>
#include <iostream>

#include "generictask.h"

class ChangeTask : public GenericTask {
    public:
        ChangeTask() : GenericTask(0, false, 0, 0, 0, "", "", 0), idGroupTask(0), idUser(0) {}
        void printInfo() {
            std::cout << "Id: " << id << std::endl;
            std::cout << "IdGroupTask: " << idGroupTask << std::endl;
            std::cout << "IdUser: " << idUser << std::endl;
            std::cout << "IsFinished: " << isFinished << std::endl;
            std::cout << "TimePlanned: " << timePlanned << std::endl;
            std::cout << "TimeDoingTask: " << timeDoingTask << std::endl;
            std::cout << "TimeDeadline: " << timeDeadline << std::endl;
            std::cout << "Title: " << title  << std::endl;
            std::cout << "Description:  " << description  << std::endl;
            std::cout << "Priority:  " << (uint64_t)priority  << std::endl;
        }
        // Геттеры
        uint64_t getIdGroupTask() { return idGroupTask; }
        uint64_t getIdUser() { return idUser; }
        // Сеттеры
        void setIdGroupTask(uint64_t idGroupTask) { this->idGroupTask = idGroupTask; }
        void setIdUser(uint64_t idUser) { this->idUser = idUser; }
    private:
        uint64_t idGroupTask;       // id группы задач (Foreign Key)
        uint64_t idUser;            // id пользователя (Foreign Key)
};