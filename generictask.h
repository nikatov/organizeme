#pragma once

#include <cinttypes>
#include <string>

class GenericTask {
    protected:
        // Объявляем protected конструктор, чтобы потом использовать его в списках инициализации
        // дочерних классов и к нему не было доступа извне
        GenericTask(int64_t id, int64_t idGroupTask, int64_t idUser, bool isFinished,
        int64_t timePlanned, int64_t timeDoingTask, int64_t timeDeadline, std::string title,
        std::string description, int8_t priority) : id(id), idGroupTask(idGroupTask),
        idUser(idUser), isFinished(isFinished), timePlanned(timePlanned), timeDoingTask(timeDoingTask),
        timeDeadline(timeDeadline), title(title), description(description), priority(priority) {}
        int64_t id;                // id задачи
        int64_t idGroupTask;       // id группы задач (Foreign Key)
        int64_t idUser;            // id пользователя (Foreign Key)
        bool isFinished;            // Флаг выполнения
        int64_t timePlanned;       // Запланированная дата (когда начать выполнять?) (секунд с начала эпохи)
        int64_t timeDoingTask;     // Временные затраты на выполнение задачи   (просто секунд)
        int64_t timeDeadline;      // Крайний срок выполнения  (секунд с начала эпохи)
        std::string title;          // Заголовок
        std::string description;    // Описание
        int8_t priority;           // Приоритет (число от 0 до 127)
};