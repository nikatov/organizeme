# Список файлов, состовляющих данный модуль
set(SRC_FILES barrier.cpp gauss.cpp)
set(INCLUDE_FILES barrier.h gauss.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/module_example_3/ INCLUDE_FILES)

# Список модулей для линковки
# set(LINK_LIBS example)

# Добавить в сборку статическую библиотеку "module_example_3":
add_library(module_example_3 STATIC ${SRC_FILES} ${INCLUDE_FILES})

# Прилинковать модули из LINK_LIBS
# target_link_libraries(module_example_3 ${LINK_LIBS})

# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "module_example_3/header.h"
target_include_directories(module_example_3 PRIVATE include/module_example_3)
target_include_directories(module_example_3 INTERFACE include)
