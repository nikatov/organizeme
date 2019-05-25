#pragma once

#include <cinttypes>
#include <string>

class GenericTask {
    public:
        // Геттеры
        uint64_t getId() { return id; }
        bool getIsFinished() { return isFinished; }
        uint64_t getTimePlanned() { return timePlanned; }
        uint64_t getTimeDoingTask() { return timeDoingTask; }
        uint64_t getTimeDeadline() { return timeDeadline; }
        std::string getTitle() { return title; }
        std::string getDescription() { return description; }
        uint8_t getPriority() { return priority; }
        // Сеттеры
        void setId(uint64_t id) { this->id = id; }
        void setIsFinished(bool isFinished) { this->isFinished = isFinished; }
        void setTimePlanned(uint64_t timePlanned) { this->timePlanned = timePlanned; }
        void setTimeDoingTask(uint64_t timeDoingTask) { this->timeDoingTask = timeDoingTask; }
        void setTimeDeadline(uint64_t timeDeadline) { this->timeDeadline = timeDeadline; }
        void setTitle(std::string title) { this->title = title; }
        void setDescription(std::string description) { this->description = description; }
        void setPriority(uint8_t priority) { this->priority = priority; }
    protected:
        // Объявляем protected конструктор, чтобы потом использовать его в списках инициализации
        // дочерних классов и к нему не было доступа извне
        GenericTask(uint64_t id, bool isFinished, uint64_t timePlanned, uint64_t timeDoingTask,
                    uint64_t timeDeadline, std::string title, std::string description, uint8_t priority) :
                    id(id), isFinished(isFinished), timePlanned(timePlanned), timeDoingTask(timeDoingTask),
                    timeDeadline(timeDeadline), title(title), description(description), priority(priority) {}
        uint64_t id;                // id задачи
        // uint64_t idGroupTask;       // id группы задач (Foreign Key)
        // uint64_t idUser;            // id пользователя (Foreign Key)
        bool isFinished;            // Флаг выполнения
        uint64_t timePlanned;       // Запланированная дата (когда начать выполнять?) (секунд с начала эпохи)
        uint64_t timeDoingTask;     // Временные затраты на выполнение задачи   (просто секунд)
        uint64_t timeDeadline;      // Крайний срок выполнения  (секунд с начала эпохи)
        std::string title;          // Заголовок
        std::string description;    // Описание
        uint8_t priority;           // Приоритет (число от 0 до 127)
};