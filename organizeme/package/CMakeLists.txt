# Список файлов, состовляющих данный модуль
set(SRC_FILES package.cpp)
set(INCLUDE_FILES changetask.h generictask.h package.h task.h user.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/package/ INCLUDE_FILES)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

# Добавить в сборку статическую библиотеку "module_example_1":
add_library(package STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(package ${Boost_LIBRARIES})

# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "package/header.h"
target_include_directories(package PRIVATE ${Boost_INCLUDE_DIR})

target_include_directories(package PRIVATE include/package)
target_include_directories(package INTERFACE include)
