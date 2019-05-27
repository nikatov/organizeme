#pragma once

#include <cinttypes>
#include <string>

class GenericUser {
    public:
        uint64_t getId() { return id; }
        std::string getUsername() { return username; }
        std::string getLastName () { return lastName; }
        std::string getFirstName () { return firstName; }
        std::string getPatronymic () { return patronymic; }        
        std::string getPassword () { return password; }           

        void setId (uint64_t id) { this->id = id; }
        void setUsername (std::string username) { this->username = username; }
        void setLastName (std::string lastName) { this->lastName = lastName; }
        void setFirstName (std::string firstName) { this->firstName = firstName; }
        void setPatronymic (std::string patronymic) { this->patronymic = patronymic; }
        void setPassword (std::string password) { this->password = password; }
    protected:
        uint64_t id;
        std::string username;
        std::string lastName;
        std::string firstName;
        std::string patronymic;
        std::string password;

        GenericUser(int64_t id, std::string username, std::string lastName, std::string firstName,
                    std::string patronymic, std::string password) : id(id), username(username), lastName(lastName),
                    firstName(firstName), patronymic(patronymic), password(password) {}

};