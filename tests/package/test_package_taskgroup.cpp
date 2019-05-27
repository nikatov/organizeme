#include <vector>
#include <memory>
#include <cassert>

#include "package/package.h"

bool testPackageTaskGroup(ChangeTaskGroup &taskGroup){
    BinaryData encoded = encodeTaskGroup(taskGroup);
    TaskGroupData taskGroupData = decodeTaskGroup(encoded.data);
    return (taskGroup.getId() == taskGroupData.taskGroup->getId() &&
            taskGroup.getIdUserGroup() == taskGroupData.taskGroup->getIdUserGroup() &&
            taskGroup.getName() == taskGroupData.taskGroup->getName());
}

int main(){
    ChangeTaskGroup taskGroup(0, 13, "Zadachi");
    ChangeTaskGroup taskGroup1(3, 0, "Zadachi");
    ChangeTaskGroup taskGroup2(3, 13, "");
    assert(testPackageTaskGroup(taskGroup));
    assert(testPackageTaskGroup(taskGroup1));
    assert(testPackageTaskGroup(taskGroup2));
    return 0;
}