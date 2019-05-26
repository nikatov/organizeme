#include "taskgroup.h"

void TaskGroup::printTasks(){
    for(auto task : tasks){
        task->printInfo();
    }
}

void TaskGroup::addTask(Task *task){
    tasks.push_back(task);
    // TODO: Послать пакет на сервер
}

void TaskGroup::changeTask(ChangeTask *changeTask){
    for(auto task : tasks){
        if(changeTask->getId() == task->getId()){
            if(changeTask->getIdGroupTask() > 0){
                // TODO: Меняем группу задач

            }
            if(changeTask->getIdUser() > 0){
                // TODO: Меняем пользователя (Нужно хранить std::vector всех пользоваетлей, которые состоят в UserGroup'ах)
            }
            if(changeTask->getIsFinished()){
                task->setIsFinished(true);
            }
            if(changeTask->getTimePlanned() > 0){
                task->setTimePlanned(changeTask->getTimePlanned());
            }
            if(changeTask->getTimeDoingTask() > 0){
                task->setTimeDoingTask(changeTask->getTimeDoingTask());
            }
            if(changeTask->getTimeDeadline() > 0){
                task->setTimeDeadline(changeTask->getTimeDeadline());
            }
            if(!changeTask->getTitle().empty()){
                task->setTitle(changeTask->getTitle());
            }
            if(!changeTask->getDescription().empty()){
                task->setDescription(changeTask->getDescription());
            }
            if(changeTask->getPriority() > 0){
                task->setPriority(changeTask->getPriority());
            }
        }
    }
    // TODO: Посылаем запрос на сервер
}

void TaskGroup::deleteTask(uint64_t idTask){
    for(uint32_t i = 0; i < tasks.size(); ++i){
        if(idTask == tasks[i]->getId()){
            delete tasks[i];
            tasks.erase(tasks.begin() + i);
            break;
        }
    }
}