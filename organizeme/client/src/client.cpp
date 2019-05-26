#include <string>
#include <iostream>

#include "client.h"

Client *Client::client = 0;

void Client::startClient(){
    std::string command;
    do {
        std::cin >> command;

        applyCommand(command);

    } while(!isExit);
}

void Client::applyCommand(std::string command){
    // Какая команда была введена?
    if(!command.compare("add")) {
        // Ввёл ли пользователь продолжение команды сразу. Если нет, то выводим подсказку
        // и ждём ввода
        addHelp();
        std::string addCommand;
        do {
            std::cin >> addCommand;
        } while(!addCommand.compare("usergroup") && !addCommand.compare("taskgroup") && !addCommand.compare("task"));
        if(!addCommand.compare("usergroup")) {
            
        } else if(!addCommand.compare("taskgroup")) {

        } else if(!addCommand.compare("task")) {

        }
    } else if(!command.compare("change")) {
        
    } else if(!command.compare("delete")) {

    } else if(!command.compare("exit")) {
        this->isExit = true;
    } else {
        std::cout << "Invalid command type!" << std::endl;
    }
}

void Client::addHelp(){
    std::cout << "Что вы хотите добавить? (usergroup/taskgroup/task)" << std::endl;
}