#pragma once

#include <string>

#include "user.h"

class Client {
    public:
        static Client* getInstance(){
            if(!client){
                client = new Client();
            }
            return client;
        }
        // Функция для начала работы клиента
        void startClient();
        User* getUser() { return user; }
    private:
        static Client *client;
        bool isExit = false;
        User *user;     // Текущий авторизованный пользователь
        // FIXME: Убрать создание юзера из конструктора
        Client() { user = new User(1, "User1", "Polokov", "Anton", "", "qwerty"); }
        Client(const Client&) {}
        Client& operator=( Client& );

        void applyCommand(std::string command);

        // Подсказки
        void addHelp();
};