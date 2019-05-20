#include <vector>

#include "package/package.h"

int main(){
    std::vector<ChangeTask> tasks;
    ChangeTask task(ADD);
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

    uint8_t *package = encodePackage(10, "AWWWWA", tasks);

    std::vector<ChangeTask> recievedTasks;
    recievedTasks = decodePackage(package);

    recievedTasks.at(0).printInfo();

    delete[] package;

    return 0;
}
