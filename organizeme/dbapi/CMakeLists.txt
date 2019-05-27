# Список файлов, состовляющих данный модуль
set(SRC_FILES core.cpp taskconnector.cpp taskgroupconnector.cpp userconnector.cpp usergroupconnector.cpp)
set(INCLUDE_FILES core.h taskconnector.h taskgroupconnector.h userconnector.h usergroupconnector.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/dbapi/ INCLUDE_FILES)

# Прилинковать либы:
add_library(dbapi STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(dbapi package ${PQXX_LIBRARIES})

target_include_directories(dbapi PRIVATE ${PQXX_INCLUDE_DIRECTORIES})
# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "package/header.h"
target_include_directories(dbapi PRIVATE include/dbapi)
target_include_directories(dbapi INTERFACE include)
