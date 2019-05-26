#include <vector>
#include <memory>

#include "package/package.h"

int main(){
    std::shared_ptr<Header> h(new Header());
    h->idUser = 10;
    h->password = "HelloWorld";
    h->opType = ADD_TASK;
    h->numOfOperations = 1;

    h->printInfo();
    uint8_t *header = encodeHeader(h);
    std::shared_ptr<Header> h2 = decodeHeader(header);

    h2->printInfo();

    // Тестирование передачи данных Task
    std::cout << "Test Task ------------------------" << std::endl;
    std::vector<ChangeTask> tasks;
    ChangeTask task;
    task.setId(1);
    task.setIdGroupTask(2);
    task.setIdUser(0);
    task.setIsFinished(true);
    task.setTimePlanned(0);
    task.setTimeDoingTask(0);
    task.setTimeDeadline(6);
    task.setTitle("Hello");
    task.setDescription("world");
    task.setPriority(9);
    tasks.push_back(task);

    task.printInfo();

    uint8_t *package = encodePackage(h, tasks);

    std::shared_ptr<Package> decodedPackage = decodePackage(package);

    switch (decodedPackage->body.which()){
        case VEC_CHANGE_USER:
            std::cout << "Not implemented!" << std::endl;
            break;
        case VEC_CHANGE_TASK:
            std::vector<ChangeTask> v = boost::get<std::vector<ChangeTask>>(decodedPackage->body);
            v.at(0).printInfo();
    }

    // тестирование передачи данных user
    std::cout << "Test User ----------------------" << std::endl;
    h->opType = ADD_USER;
    std::vector<ChangeUser> users;
    ChangeUser user(1, "2", "3", "4", "5", "6");
    user.printInfo();
    users.push_back(user);
    uint8_t *encUser = encodePackage(h, users);
    decodedPackage = decodePackage(encUser);
    if(decodedPackage->body.which() == VEC_CHANGE_USER){
        std::vector<ChangeUser> v = boost::get<std::vector<ChangeUser>>(decodedPackage->body);
        v.at(0).printInfo();
    }

    // Тестируем передачу UserGroup
    std::cout << "Test UserGroup ---------------" << std::endl;
    h->opType = ADD_USER_GROUP;
    h->numOfOperations = 2;
    std::vector<ChangeUserGroup> userGroups;
    ChangeUserGroup userGroup1(1, "Spartans", false);
    userGroup1.printInfo();
    ChangeUserGroup userGroup2(2, "Romans", true);
    userGroup2.printInfo();
    userGroups.push_back(userGroup1);
    userGroups.push_back(userGroup2);
    uint8_t *encUserGroup = encodePackage(h, userGroups);
    decodedPackage = decodePackage(encUserGroup);
    if(decodedPackage->body.which() == VEC_CHANGE_USER_GROUP){
        std::vector<ChangeUserGroup> v = boost::get<std::vector<ChangeUserGroup>>(decodedPackage->body);
        v.at(0).printInfo();
        v.at(1).printInfo();
    }

    // Тестирование передачи данных taskGroup
    std::cout << "Test taskGroup ----------------" << std::endl;
    h->opType = ADD_TASK_GROUP;
    ChangeTaskGroup chTaskGroup1(1, 2, "TASK#1");
    chTaskGroup1.printInfo();
    ChangeTaskGroup chTaskGroup2(55, 0, "");
    chTaskGroup2.printInfo();
    std::vector<ChangeTaskGroup> chTaskGroups;
    chTaskGroups.push_back(chTaskGroup1);
    chTaskGroups.push_back(chTaskGroup2);
    uint8_t *encTaskGroups = encodePackage(h, chTaskGroups);
    decodedPackage = decodePackage(encTaskGroups);
    if(decodedPackage->body.which() == VEC_CHANGE_TASK_GROUP){
        auto v = boost::get<std::vector<ChangeTaskGroup>>(decodedPackage->body);
        v.at(0).printInfo();
        v.at(1).printInfo();
    }

    delete[] header;
    delete[] package;
    delete[] encUser;
    delete[] encUserGroup;
    delete[] encTaskGroups;

    return 0;
}
