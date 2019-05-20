# Список файлов, состовляющих данный модуль
set(SRC_FILES grapher.cpp)
set(INCLUDE_FILES grapher.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/module_example_2/ INCLUDE_FILES)

# Список модулей для линковки
# set(LINK_LIBS example)

# Добавить в сборку статическую библиотеку "module_example_2":
add_library(module_example_2 STATIC ${SRC_FILES})

# Прилинковать модули из LINK_LIBS
# target_link_libraries(module_example_2 ${LINK_LIBS})

# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "module_example_2/header.h"
target_include_directories(module_example_2 PRIVATE include/module_example_2)
target_include_directories(module_example_2 INTERFACE include)
