#pragma once

#include <cinttypes>
#include <string>

#include "package/generictask.h"

class TaskGroup;

class Task : public GenericTask{
    public:
        // FIXME: Прикрутить нормальный конструктор
        Task(uint64_t id, TaskGroup *taskGroup, std::string title) :
            GenericTask(id, false, 0, 0, 0, title, "", 3) {}
        
        TaskGroup* getTaskGroup() { return taskGroup; }    
    private:
        TaskGroup *taskGroup;       // Указатель на группу задач, которой принадлежит текущая задача
};