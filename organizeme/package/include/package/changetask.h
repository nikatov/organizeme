#pragma once

#include <cinttypes>
#include <string>
#include <iostream>

#include "generictask.h"

enum operationType {ADD, CHANGE, DELETE};

class ChangeTask : private GenericTask {
    public:
        ChangeTask(operationType opType) : GenericTask(-1, -1, -1, false, -1, -1, -1, "", "", -1) {}
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
        int64_t getId() { return id; }
        int64_t getIdGroupTask() { return idGroupTask; }
        int64_t getIdUser() { return idUser; }
        bool getIsFinished() { return isFinished; }
        int64_t getTimePlanned() { return timePlanned; }
        int64_t getTimeDoingTask() { return timeDoingTask; }
        int64_t getTimeDeadline() { return timeDeadline; }
        std::string getTitle() { return title; }
        std::string getDescription() { return description; }
        int8_t getPriority() { return priority; }
        operationType getOperationType() { return opType; }
        // Сеттеры
        void setId(int64_t id) { this->id = id; }
        void setIdGroupTask(int64_t idGroupTask) { this->idGroupTask = idGroupTask; }
        void setIdUser(int64_t idUser) { this->idUser = idUser; }
        void setIsFinished(bool isFinished) { this->isFinished = isFinished; }
        void setTimePlanned(int64_t timePlanned) { this->timePlanned = timePlanned; }
        void setTimeDoingTask(int64_t timeDoingTask) { this->timeDoingTask = timeDoingTask; }
        void setTimeDeadline(int64_t timeDeadline) { this->timeDeadline = timeDeadline; }
        void setTitle(std::string title) { this->title = title; }
        void setDescription(std::string description) { this->description = description; }
        void setPriority(int8_t priority) { this->priority = priority; }
        void setOperationType(operationType opType) { this->opType = opType; }
    private:
        operationType opType;
};