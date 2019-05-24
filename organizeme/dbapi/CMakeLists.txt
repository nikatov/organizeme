# Список файлов, состовляющих данный модуль
set(SRC_FILES select.cpp)
set(INCLUDE_FILES select.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/dbapi/ INCLUDE_FILES)

# Указать директории хэдеров:
find_package(PQXX)
include_directories(${PQXX_INCLUDE_DIRECTORIES})

# Прилинковать либы:
add_library(dbapi STATIC ${SRC_FILES} ${INCLUDE_FILES} ${PQXX_LIBRARIES})

# set_target_properties(dbapi PROPERTIES LINKER_LANGUAGE CXX)
# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "package/header.h"
target_include_directories(dbapi PRIVATE include/dbapi)
target_include_directories(dbapi INTERFACE include)
