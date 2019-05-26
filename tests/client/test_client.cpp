#include "client/client.h"

int main(){
    Client *client = Client::getInstance();
    std::cout << "Добавляем userGroup: " << std::endl;
    client->getUser()->addUserGroup(new UserGroup(1, "MyGroup", true));
    client->getUser()->printUserGroups();
    std::cout << "Добавляем ещё userGroup: " << std::endl;
    client->getUser()->addUserGroup(new UserGroup(2, "PUBG", false));
    client->getUser()->printUserGroups();
    std::cout << "Изменяем имя userGroup с id == 1: " << std::endl;
    client->getUser()->changeUserGroup(new ChangeUserGroup(1, "MYCHANGEDGROUP", false));
    client->getUser()->printUserGroups();
    std::cout << "Удаляем userGroup с id == 1: " << std::endl;
    client->getUser()->deleteUserGroup(1);
    client->getUser()->printUserGroups();

    return 0;
}