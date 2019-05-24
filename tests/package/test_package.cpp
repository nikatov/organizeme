#include <vector>

#include "package/package.h"

int main(){
    Header h;
    h.idUser = 10;
    h.password = "HelloWorld";
    h.opType = ADD_TASK;
    h.numOfOperations = 1;

    h.printInfo();
    uint8_t *header = encodeHeader(h);
    Header *h2 = decodeHeader(header);

    h2->printInfo();

    // Тестирование передачи данных Task
    std::cout << "Task: " << std::endl;
    std::vector<ChangeTask> tasks;
    ChangeTask task;
    task.setId(1);
    task.setIdGroupTask(2);
    task.setIdUser(3);
    task.setIsFinished(true);
    task.setTimePlanned(4);
    task.setTimeDoingTask(5);
    task.setTimeDeadline(6);
    task.setTitle("Hello");
    task.setDescription("world");
    task.setPriority(9);
    tasks.push_back(task);

    task.printInfo();

    uint8_t *package = encodePackage(h, tasks);

    Package* decodedPackage = decodePackage(package);

    switch (decodedPackage->body.which()){
        case VEC_CHANGE_USER:
            std::cout << "Not implemented!" << std::endl;
            break;
        case VEC_CHANGE_TASK:
            std::vector<ChangeTask> v = boost::get<std::vector<ChangeTask>>(decodedPackage->body);
            v.at(0).printInfo();
    }

    // тестирование передачи данных user
    h.opType = ADD_USER;
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
    // delete[] decodedPackage;

    return 0;
}
