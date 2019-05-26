# Список файлов, состовляющих данный модуль
set(SRC_FILES TaskConnector.cpp)
set(INCLUDE_FILES TaskConnector.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/dbapi/ INCLUDE_FILES)

# Прилинковать либы:
add_library(dbapi STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(dbapi package pqxx ${PQXX_LIBRARIES})

target_include_directories(dbapi PRIVATE ${PQXX_INCLUDE_DIRECTORIES})
# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "package/header.h"
target_include_directories(dbapi PRIVATE include/dbapi)
target_include_directories(dbapi INTERFACE include)
