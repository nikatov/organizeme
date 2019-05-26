#include "usergroup.h"

void UserGroup::printTaskGroups(){
    for(auto taskGroup : taskGroups){
        taskGroup->printInfo();
    }
}

void UserGroup::addTaskGroup(TaskGroup  *taskGroup){
    taskGroups.push_back(taskGroup);
    // TODO: Пересылка на сервер
}

void UserGroup::changeTaskGroup(ChangeTaskGroup *changeTaskGroup){
    for(auto taskGroup : taskGroups){
        if(changeTaskGroup->getId() == taskGroup->getId()){
            if(!changeTaskGroup->getName().empty()){
                taskGroup->setName(changeTaskGroup->getName());
            }
        }
    }
    // TODO: Пересылка на сервер
}

void UserGroup::deleteTaskGroup(uint64_t idTaskGroup){
    for(uint32_t i = 0; i < taskGroups.size(); ++i){
        if(idTaskGroup == taskGroups[i]->getId()){
            // FIXME: Надо удалять все task'и из taskGroup. Для других классов по аналогии
            delete taskGroups[i];
            taskGroups.erase(taskGroups.begin() + i);
        }
    }
    // TODO: Пересылка на сервер
}