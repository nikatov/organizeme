#pragma once

#include <cinttypes>
#include <string>
#include <vector>
#include <iostream>
#include <boost/variant.hpp>

#include "changetask.h"
#include "changeuser.h"

enum operationType {ADD_USER, CHANGE_USER, DELETE_USER, ADD_TASK, CHANGE_TASK, DELETE_TASK, ADD_TASK_GROUP, CHANGE_TASK_GROUP,
                    DELETE_TASK_GROUP, ADD_USER_GROUP, CHANGE_USER_GROUP, DELETE_USER_GROUP,
                    };

struct Data {
    uint32_t size;
    Data(uint32_t size) : size(size) {}
};

struct BinaryData : Data {
    uint8_t *data;
    BinaryData(uint8_t *data, uint32_t size) : Data(size), data(data) {}
};

struct TaskData : Data {
    ChangeTask *task;
    TaskData(ChangeTask *task, uint32_t size) : Data(size), task(task) {}
};

struct UserData : Data {
    ChangeUser *user;
    UserData(ChangeUser *user, uint32_t size) : Data(size), user(user) {}
};

struct Header {
    uint64_t idUser;
    std::string password;
    uint32_t numOfOperations;
    operationType opType;

    void printInfo() {
        std::cout << "------- HEADER --------" << std::endl;
        std::cout << "IdUser: " << idUser << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << "NumOfOperations: " << numOfOperations << std::endl;
        std::cout << "OperationType: " << opType << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
};

enum packageType {VEC_CHANGE_USER, VEC_CHANGE_TASK};

struct Package {
    Header *header;
    boost::variant<std::vector<ChangeUser>, std::vector<ChangeTask>> body;
    Package(Header *header, boost::variant<std::vector<ChangeUser>, std::vector<ChangeTask>> body) :
                    header(header), body(body) {}
};

uint8_t* encodePackage(Header &h, std::vector<ChangeUser> users);
uint8_t* encodePackage(Header &h, std::vector<ChangeTask> tasks);

Package* decodePackage(uint8_t *package);
// Выделяет 44 байта на куче, формирует header и возвращает указатель на 44 байта
uint8_t* encodeHeader(Header h);

Header* decodeHeader(uint8_t *package);

BinaryData encodeTask(ChangeTask task);

TaskData decodeTask(uint8_t *package);

BinaryData encodeUser(ChangeUser user);

UserData decodeUser(uint8_t *package);

// Функция нужна для записи в переменной размером больше 1 байта в 
// участок массива uint8_t
void writeBytes(uint16_t src, uint8_t *dst);

void writeBytes(uint32_t src, uint8_t *dst);

void writeBytes(uint64_t src, uint8_t *dst);

// Первые 2 байта записывает размер строки, потом пишет строку
void writeBytes(std::string src, uint8_t *dst);

void getBytes(uint8_t *src, uint16_t *dst);