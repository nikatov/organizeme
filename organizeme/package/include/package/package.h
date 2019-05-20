#pragma once

#include <cinttypes>
#include <string>
#include <vector>

#include "changetask.h"

struct TaskData {
    uint8_t *data;
    uint32_t size;

    TaskData(uint8_t *data, uint32_t size) : data(data), size(size) {}
};

uint8_t* encodePackage(int64_t idUser, std::string password, std::vector<ChangeTask> tasks);

std::vector<ChangeTask> decodePackage(uint8_t *package);
// Выделяет 44 байта на куче, формирует header и возвращает указатель на 44 байта
uint8_t* getHeader(uint32_t numOfOperations, uint64_t idUser, std::string password);

TaskData getTask(ChangeTask task);

// Функция нужна для записи в переменной размером больше 1 байта в 
// участок массива uint8_t
void writeBytes(uint16_t src, uint8_t *dst);

void writeBytes(uint32_t src, uint8_t *dst);

void writeBytes(uint64_t src, uint8_t *dst);

// Первые 2 байта записывает размер строки, потом пишет строку
void writeBytes(std::string src, uint8_t *dst);

void getBytes(uint8_t *src, uint16_t *dst);