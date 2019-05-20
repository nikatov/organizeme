#pragma once

#include <cinttypes>
#include <string>

#include "generictask.h"

class Task : private GenericTask {
    public:
        Task() = delete;
    private:
        int64_t timeCreation;      // Время создания задачи (секунд с начала эпохи)
};