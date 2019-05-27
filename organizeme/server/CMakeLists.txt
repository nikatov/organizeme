# Список файлов, состовляющих данный модуль
set(SRC_FILES server.cpp)
set(INCLUDE_FILES server.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/server/ INCLUDE_FILES)

# Добавить в сборку статическую библиотеку "server":
add_library(server STATIC ${SRC_FILES} ${INCLUDE_FILES})

# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "server/header.h"
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIR})

target_include_directories(server PRIVATE include/server)
target_include_directories(server INTERFACE include)
