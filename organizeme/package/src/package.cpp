#include "../include/package/package.h"

uint8_t* encodePackage(Header &h, std::vector<ChangeTask> tasks) {
    // Закодируем заголовок
    uint8_t *header = encodeHeader(h);
    std::vector<BinaryData> tasksEncoded;
    // Размер заголовка -- 48 байт
    uint64_t packageSize = 48;
    // Кодируем все переданные таски и вычисляем общий размер пакета
    for(int i = 0; i < tasks.size(); ++i){
        tasksEncoded.push_back(encodeTask(tasks.at(i)));
        packageSize += tasksEncoded.at(i).size;
    }
    // Выделяем память под пакет
    uint8_t *package = new uint8_t[packageSize];
    // Записываем заголовок в пакет
    for(int i = 0; i < 48; ++i){
        package[i] = header[i];
    }
    uint64_t curPackageSize = 48;
    // Записываем таски в пакет
    for(int k = 0; k < tasksEncoded.size(); ++k){
        for(int i = 0; i < tasksEncoded.at(k).size; ++i){
            package[curPackageSize] = tasksEncoded.at(k).data[i];
            ++curPackageSize;
        }
    }
    // Освобождаем память
    delete[] header;
    for(int i = 0; i < tasksEncoded.size(); ++i){
        delete[] tasksEncoded.at(i).data;
    }
    // Возвращаем результат
    return package;
}

std::vector<ChangeTask> decodePackage(uint8_t *package) {
    Header *h = decodeHeader(package);
    std::vector<ChangeTask> changeTasks;
    uint32_t pointerOffset = 48;
    for(int k = 0; k < h->numOfOperations; ++k){
        // operationType opType = (operationType)((uint8_t) *(package + pointerOffset));
        TaskData taskData = decodeTask(package + pointerOffset);
        pointerOffset += taskData.size;
        changeTasks.push_back(*taskData.task);
    }
    return changeTasks;
}

// Выделяет 48 байта на куче, формирует header и возвращает указатель на 48 байта
// 0-8 байт -- idUser, 8-40 байт -- password, 40-44 байт -- operationType, 44-48 -- numOfOpeartions
uint8_t* encodeHeader(Header h){
    uint8_t *header = new uint8_t[48];
    writeBytes(h.idUser, header);
    for(int i = 0; i < h.password.size() && i < 31; ++i){
        header[8 + i] = (uint8_t)h.password.at(i);
    }
    if(h.password.size() < 31){
        header[8 + h.password.size()] = '\0';
    } else {
        header[8 + 31] = '\0';
    }
    writeBytes((uint32_t)h.opType, header+40);
    writeBytes(h.numOfOperations, header+44);
    return header;
}

// Декодирует массив uint8_t* в Header* 
Header* decodeHeader(uint8_t *package){
    Header *h = new Header();
    h->idUser = (uint64_t) *(package);
    std::string password((char *)(package + 8));
    h->password = password;
    h->opType = (operationType) *(package + 40);
    h->numOfOperations = (uint32_t) *(package + 44);  
    return h;
}

// Кодирует одну задачу в структуру, в которой хранится массив uint8_t и размер массива
BinaryData encodeTask(ChangeTask task){   
    // uint8_t opType = task.getOperationType();          // Тип операции
    uint16_t changeFlags = 0;       // Флаги изменения
    uint64_t sizeBytes = 2;
    if(task.getId() >= 0) {
        changeFlags |= 0x0001;
        sizeBytes += 8;
    }
    if(task.getIdGroupTask() >= 0) {
        changeFlags |= 0x0002;
        sizeBytes += 8;
    }
    if(task.getIdUser() >= 0) {
        changeFlags |= 0x0004;
        sizeBytes += 8;
    }
    if(task.getIsFinished()) {
        changeFlags |= 0x0008;
        sizeBytes += 1;
    }
    if(task.getTimePlanned() >= 0) {
        changeFlags |= 0x0010;
        sizeBytes += 8;
    }
    if(task.getTimeDoingTask() >= 0) {
        changeFlags |= 0x0020;
        sizeBytes += 8;
    }
    if(task.getTimeDeadline() >= 0) {
        changeFlags |= 0x0040;
        sizeBytes += 8;
    }
    if(!task.getTitle().empty()) {
        changeFlags |= 0x0080;
        sizeBytes += task.getTitle().size() + 2;    // 2-байта под размер перед блоком
    }
    if(!task.getDescription().empty()) {
        changeFlags |= 0x0100;
        sizeBytes += task.getDescription().size() + 2;  // 2-байта под размер перед блоком
    }
    if(task.getPriority() >= 0) {
        changeFlags |= 0x0200;
        sizeBytes += 1;
    }
    BinaryData taskData(new uint8_t[sizeBytes], sizeBytes);  // ChangeTask в массиве байт
    // taskData.data[0] = (uint8_t) opType;
    writeBytes(changeFlags, (taskData.data));
    uint32_t pointerOffset = 2;
    if(task.getId() >= 0) {
        writeBytes((uint64_t)task.getId(), taskData.data + pointerOffset);
        pointerOffset += 8;
    }
    if(task.getIdGroupTask() >= 0) {
        writeBytes((uint64_t)task.getIdGroupTask(), taskData.data + pointerOffset);
        pointerOffset += 8;
    }
    if(task.getIdUser() >= 0) {
        writeBytes((uint64_t)task.getIdUser(), taskData.data + pointerOffset);
        pointerOffset += 8;
    }
    if(task.getIsFinished()) {
        taskData.data[pointerOffset] = 1;
        pointerOffset += 1;
    }
    if(task.getTimePlanned() >= 0) {
        writeBytes((uint64_t)task.getTimePlanned(), taskData.data + pointerOffset);
        pointerOffset += 8;
    }
    if(task.getTimeDoingTask() >= 0) {
        writeBytes((uint64_t)task.getTimeDoingTask(), taskData.data + pointerOffset);
        pointerOffset += 8;
    }
    if(task.getTimeDeadline() >= 0) {
        writeBytes((uint64_t)task.getTimeDeadline(), taskData.data + pointerOffset);
        pointerOffset += 8;
    }
    if(!task.getTitle().empty()) {
        writeBytes(task.getTitle(), (taskData.data + pointerOffset));
        pointerOffset += task.getTitle().size() + 2;
    }
    if(!task.getDescription().empty()) {
        writeBytes(task.getDescription(), (taskData.data + pointerOffset));
        pointerOffset += task.getDescription().size() + 2;
    }
    if(task.getPriority() >= 0) {
        taskData.data[pointerOffset] = task.getPriority();
    }
    return taskData;
}

TaskData decodeTask(uint8_t *package){
    ChangeTask *task = new ChangeTask();
    uint32_t pointerOffset = 0;
    uint16_t changeFlags = 0;
    getBytes((package + pointerOffset), &changeFlags);
    pointerOffset += 2;
    if(changeFlags & 0x0001){
        task->setId((int64_t) *(package + pointerOffset));
        pointerOffset += 8;
    }
    if(changeFlags & 0x0002){
        task->setIdGroupTask((int64_t) *(package + pointerOffset));
        pointerOffset += 8;
    }
    if(changeFlags & 0x0004){
        task->setIdUser((int64_t) *(package + pointerOffset));
        pointerOffset += 8;
    }
    if(changeFlags & 0x0008){
        uint8_t isFinished = *(package + pointerOffset);
        if(isFinished != 0) {
            task->setIsFinished(true);
        }
        pointerOffset += 1;
    }
    if(changeFlags & 0x0010){
        task->setTimePlanned((int64_t) *(package + pointerOffset));
        pointerOffset += 8;
    }
    if(changeFlags & 0x0020){
        task->setTimeDoingTask((int64_t) *(package + pointerOffset));
        pointerOffset += 8;
    }
    if(changeFlags & 0x0040){
        task->setTimeDeadline((int64_t) *(package + pointerOffset));
        pointerOffset += 8;
    }
    if(changeFlags & 0x0080){
        uint16_t stringSize = (uint16_t) *(package + pointerOffset);
        pointerOffset += 2;
        std::string title;
        for(int i = 0; i < stringSize; ++i){
            title.push_back((char) *(package + pointerOffset + i));
        }
        task->setTitle(title);
        pointerOffset += stringSize;
    }
    if(changeFlags & 0x0100){
        uint16_t stringSize = (uint16_t) *(package + pointerOffset);
        pointerOffset += 2;
        std::string description;
        for(int i = 0; i < stringSize; ++i){
            description.push_back((char) *(package + pointerOffset + i));
        }
        task->setDescription(description);
        pointerOffset += stringSize;
    }
    if(changeFlags & 0x0200){
        task->setPriority(*(package + pointerOffset));
        pointerOffset += 1;
    }
    return TaskData(task, pointerOffset);
}

// FIXME: Проверить как улучшить функцию
// FIXME: std::copy(&src, &src+1, dst)
// Функция нужна для записи в переменной размером больше 1 байта в 
// участок массива uint8_t
void writeBytes(uint16_t src, uint8_t *dst){
    uint8_t *src_p = (uint8_t*)&src;
    for(int i = 0; i < 2; ++i){
        dst[i] = src_p[i];
    }
}

void writeBytes(uint32_t src, uint8_t *dst){
    uint8_t *src_p = (uint8_t*)&src;
    for(int i = 0; i < 4; ++i){
        dst[i] = src_p[i];
    }
}

void writeBytes(uint64_t src, uint8_t *dst){
    uint8_t *src_p = (uint8_t*)&src;
    for(int i = 0; i < 8; ++i){
        dst[i] = src_p[i];
    }
}

// Первые 2 байта записывает размер строки, потом пишет строку
void writeBytes(std::string src, uint8_t *dst){
    writeBytes((uint16_t)src.size(), dst);
    for(int i = 0; i < src.size(); ++i){
       dst[2 + i] = src.at(i);
    }
}

void getBytes(uint8_t *src, uint16_t *dst){
    uint8_t *dst_ptr = (uint8_t *)dst;
    for(int i = 0; i < 2; ++i){
        dst_ptr[i] = src[i];
    }
}

void getBytes(uint8_t *src, uint32_t *dst){
    uint8_t *dst_ptr = (uint8_t *)dst;
    for(int i = 0; i < 4; ++i){
        dst_ptr[i] = src[i];
    }
}

void getBytes(uint8_t *src, uint64_t *dst){
    uint8_t *dst_ptr = (uint8_t *)dst;
    for(int i = 0; i < 8; ++i){
        dst_ptr[i] = src[i];
    }
}