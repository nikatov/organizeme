#pragma once

#include <cstdint>
#include <string>

class User {
    public:
        uint64_t getId() { return id; }
        void setId(uint64_t id) { this->id = id; }
        std::string getUserName() { return userName; }
        void setUserName(std::string userName) { this->userName = userName; }
        std::string getLastName() { return lastName; }
        void setLastName(std::string lastName) { this->userName = lastName; }
        std::string getFirstName() { return firstName; }
        void setFirstName(std::string firstName) { this->userName = firstName; }
        std::string getPatronymic() { return patronymic; }
        void setPatronymic(std::string patronymic) { this->patronymic = patronymic; }
        uint64_t getCreationTime() { return creationTime; }
    private:
        uint64_t id;                // id юзера
        std::string userName;       // Логин
        std::string lastName;       // Фамилия
        std::string firstName;      // Имя
        std::string patronymic;     // Отчество
        std::string password;       // Пароль
        uint64_t creationTime;              // Время в секундах от начала эпохи
};