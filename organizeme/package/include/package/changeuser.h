#pragma once

#include <string>
#include <cinttypes>

class ChangeUser {
    public:
        ChangeUser() : id(-1), username(""), lastName(""), firstName(""), patronymic(""), password("") {}
        ChangeUser(int64_t id, std::string username, std::string lastName, std::string firstName,
            std::string patronymic, std::string password) : id(id), username(username), lastName(lastName),
            firstName(firstName), patronymic(patronymic), password(password) {}

        void printInfo(){
            std::cout << "Id: " << id << std::endl;
            std::cout << "Username: " << username << std::endl;
            std::cout << "LastName: " << lastName << std::endl;
            std::cout << "FirstName: " << firstName << std::endl;
            std::cout << "Patronymic: " << patronymic << std::endl;
            std::cout << "Password: " << password << std::endl;
        }

        int64_t getId() { return id; }
        std::string getUsername() { return username; }
        std::string getLastName () { return lastName; }
        std::string getFirstName () { return firstName; }
        std::string getPatronymic () { return patronymic; }        
        std::string getPassword () { return password; }           

        void setId (int64_t id) { this->id = id; }
        void setUsername (std::string username) { this->username = username; }
        void setLastName (std::string lastName) { this->lastName = lastName; }
        void setFirstName (std::string firstName) { this->firstName = firstName; }
        void setPatronymic (std::string patronymic) { this->patronymic = patronymic; }
        void setPassword (std::string password) { this->password = password; }
    private:
        int64_t id;
        std::string username;
        std::string lastName;
        std::string firstName;
        std::string patronymic;
        std::string password;
};