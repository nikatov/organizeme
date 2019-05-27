#include <vector>
#include <memory>
#include <cassert>

#include "package/package.h"

bool testPackageTask(ChangeTask &task){
    BinaryData encoded = encodeTask(task);
    TaskData taskData = decodeTask(encoded.data);
    return (task.getId() == taskData.task->getId() && task.getIdGroupTask() == taskData.task->getIdGroupTask() &&
            task.getIdUser() == taskData.task->getIdUser() && task.getIsFinished() == taskData.task->getIsFinished() &&
            task.getTimePlanned() == taskData.task->getTimePlanned() && task.getTimeDoingTask() ==
            taskData.task->getTimeDoingTask() && task.getTimeDeadline() == taskData.task->getTimeDeadline() &&
            task.getTitle() == taskData.task->getTitle() && task.getDescription() == taskData.task->getDescription() &&
            task.getPriority() == taskData.task->getPriority());
}

int main(){
    ChangeTask task(0, 2, 3, true, 10, 15, 20, "Title", "Description", 8);
    ChangeTask task1(1, 0, 3, true, 10, 15, 20, "Title", "Description", 8);
    ChangeTask task2(1, 2, 0, true, 10, 15, 20, "Title", "Description", 8);
    ChangeTask task3(1, 2, 3, false, 0, 15, 20, "Title", "Description", 8);
    ChangeTask task4(1, 2, 3, true, 10, 0, 20, "Title", "Description", 8);
    ChangeTask task5(1, 2, 3, true, 10, 15, 0, "Title", "Description", 8);
    ChangeTask task6(1, 2, 3, true, 10, 15, 20, "", "Description", 8);
    ChangeTask task7(1, 2, 3, true, 10, 15, 20, "Title", "", 8);
    ChangeTask task8(1, 2, 3, true, 10, 15, 20, "Title", "Description", 0);
    assert(testPackageTask(task));
    assert(testPackageTask(task1));
    assert(testPackageTask(task2));
    assert(testPackageTask(task3));
    assert(testPackageTask(task4));
    assert(testPackageTask(task5));
    assert(testPackageTask(task6));
    assert(testPackageTask(task7));
    assert(testPackageTask(task8));
    return 0;
}