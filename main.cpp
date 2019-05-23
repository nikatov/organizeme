#include <vector>

#include "organizeme/package/include/package/package.h"

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

    std::vector<ChangeTask> recievedTasks;
    recievedTasks = decodePackage(package);

    recievedTasks.at(0).printInfo();

    delete[] package;

    return 0;
}
