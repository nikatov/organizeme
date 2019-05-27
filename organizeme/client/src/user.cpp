#include <memory>

#include "user.h"

void User::printUserGroups(){
    for(auto userGroup : userGroups){
        userGroup->printInfo();
    }
}

void User::addUserGroup(UserGroup *userGroup){
    userGroups.push_back(userGroup);
    // TODO: Пересылка на сервер
}

std::unique_ptr<ChangeUserGroup> User::changeUserGroup(std::unique_ptr<ChangeUserGroup> changeUserGroup){
    // FIXME: Если мы меняем не локальную userGroup, то нужна дополнительная проверка на админа
    for(auto userGroup : userGroups){
        if(changeUserGroup->getId() == userGroup->getId()){
            if(!changeUserGroup->getGroupName().empty()){
                userGroup->setGroupName(changeUserGroup->getGroupName());
            }
        }
    }
    // TODO: Пересылка на сервер

    return std::move(changeUserGroup);
}

void User::deleteUserGroup(uint64_t idUserGroup){
    for(uint32_t i = 0; i < userGroups.size(); ++i){
        if(idUserGroup == userGroups[i]->getId()){
            // FIXME: Удаляем все taskGroup
            delete userGroups[i];
            userGroups.erase(userGroups.begin() + i);
        }
    }
    // TODO: Пересылка на сервер
}