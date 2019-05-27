#pragma once

#include <string>
#include <cinttypes>
#include <iostream>

#include "genericuser.h"

class ChangeUser : public GenericUser {
    public:
        ChangeUser() : GenericUser(0, "", "", "", "", "") {}
        ChangeUser(int64_t id, std::string username, std::string lastName, std::string firstName,
                   std::string patronymic, std::string password) : 
                   GenericUser(id, username, lastName, firstName, patronymic, password) {}

        void printInfo(){
            std::cout << "Id: " << id << std::endl;
            std::cout << "Username: " << username << std::endl;
            std::cout << "LastName: " << lastName << std::endl;
            std::cout << "FirstName: " << firstName << std::endl;
            std::cout << "Patronymic: " << patronymic << std::endl;
            std::cout << "Password: " << password << std::endl;
        }
};