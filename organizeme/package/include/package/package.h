#pragma once

#include <cinttypes>
#include <string>
#include <vector>
#include <iostream>
#include <boost/variant.hpp>
#include <memory>

#include "changeuser.h"
#include "changeusergroup.h"
#include "changetaskgroup.h"
#include "changetask.h"

enum operationType {
                    ADD_USER, CHANGE_USER, DELETE_USER, ADD_USER_GROUP, CHANGE_USER_GROUP, DELETE_USER_GROUP,
                    ADD_TASK_GROUP, CHANGE_TASK_GROUP, DELETE_TASK_GROUP, ADD_TASK, CHANGE_TASK, DELETE_TASK, 
                    };

struct Data {
    uint32_t size;
    Data(uint32_t size) : size(size) {}
};

struct BinaryData : Data {
    uint8_t *data;
    BinaryData(uint8_t *data, uint32_t size) : Data(size), data(data) {}
    ~BinaryData() { delete[] data; }
};

struct TaskData : Data {
    std::shared_ptr<ChangeTask> task;
    TaskData(std::shared_ptr<ChangeTask> task, uint32_t size) : Data(size), task(task) {}
};

struct UserData : Data {
    std::shared_ptr<ChangeUser> user;
    UserData(std::shared_ptr<ChangeUser> user, uint32_t size) : Data(size), user(user) {}
};

struct UserGroupData : Data {
    std::shared_ptr<ChangeUserGroup> userGroup;
    UserGroupData(std::shared_ptr<ChangeUserGroup> userGroup, uint32_t size) : Data(size), userGroup(userGroup) {}
};

struct TaskGroupData : Data {
    std::shared_ptr<ChangeTaskGroup> taskGroup;
    TaskGroupData(std::shared_ptr<ChangeTaskGroup> taskGroup, uint32_t size) : Data(size), taskGroup(taskGroup) {}
};

struct Header {
    uint64_t idUser;
    std::string password;
    uint32_t numOfOperations;
    operationType opType;

    Header(){}
    Header(uint64_t idUser, std::string password, uint32_t numOfOperations, operationType opType) :
            idUser(idUser), password(password), numOfOperations(numOfOperations), opType(opType) {}

    void printInfo() {
        std::cout << "------- HEADER --------" << std::endl;
        std::cout << "IdUser: " << idUser << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << "NumOfOperations: " << numOfOperations << std::endl;
        std::cout << "OperationType: " << opType << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
};

enum packageType {VEC_CHANGE_USER, VEC_CHANGE_USER_GROUP, VEC_CHANGE_TASK_GROUP, VEC_CHANGE_TASK};

struct Package {
    std::shared_ptr<Header> header;
    boost::variant<std::vector<ChangeUser>, std::vector<ChangeUserGroup>,
                 std::vector<ChangeTaskGroup>, std::vector<ChangeTask>> body;
    Package(
            std::shared_ptr<Header> header,
            boost::variant<std::vector<ChangeUser>, std::vector<ChangeUserGroup>,
                           std::vector<ChangeTaskGroup>, std::vector<ChangeTask>> body
            ) : header(header), body(body) {}
};

uint8_t* encodePackage(std::shared_ptr<Header> h, boost::variant<std::vector<ChangeUser>, std::vector<ChangeUserGroup>,
                       std::vector<ChangeTaskGroup>, std::vector<ChangeTask>> changeObjs);

std::shared_ptr<Package> decodePackage(uint8_t *package);
// Выделяет 44 байта на куче, формирует header и возвращает указатель на 44 байта
uint8_t* encodeHeader(std::shared_ptr<Header> h);

std::shared_ptr<Header> decodeHeader(uint8_t *package);

BinaryData encodeTask(ChangeTask task);

TaskData decodeTask(uint8_t *package);

BinaryData encodeUser(ChangeUser user);

UserData decodeUser(uint8_t *package);

BinaryData encodeUserGroup(ChangeUserGroup userGroup);

UserGroupData decodeUserGroup(uint8_t *package);

BinaryData encodeTaskGroup(ChangeTaskGroup taskGroup);

TaskGroupData decodeTaskGroup(uint8_t *package);

// Функция нужна для записи в переменной размером больше 1 байта в 
// участок массива uint8_t
void writeBytes(uint16_t src, uint8_t *dst);

void writeBytes(uint32_t src, uint8_t *dst);

void writeBytes(uint64_t src, uint8_t *dst);

// Первые 2 байта записывает размер строки, потом пишет строку
void writeBytes(std::string src, uint8_t *dst);

void getBytes(uint8_t *src, uint16_t *dst);