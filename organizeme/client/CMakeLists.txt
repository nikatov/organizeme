# Список файлов, состовляющих данный модуль
set(SRC_FILES client.cpp user.cpp usergroup.cpp taskgroup.cpp)
set(INCLUDE_FILES client.h user.h task.h taskgroup.h usergroup.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/client/ INCLUDE_FILES)

# Прилинковать либы:
add_library(client STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(client package)

# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "package/header.h"
target_include_directories(client PRIVATE include/client)
target_include_directories(client INTERFACE include)
