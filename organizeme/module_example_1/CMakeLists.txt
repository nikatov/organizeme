# Список файлов, состовляющих данный модуль
set(SRC_FILES points.cpp function.cpp lagrange.cpp qubic.cpp)
set(INCLUDE_FILES points.h function.h lagrange.h qubic.h)

# Подключаем модуль addprefix
include(addprefix)

# Добавляем необходимые префиксы к элементам списка
addprefix(src/ SRC_FILES)
addprefix(include/module_example_1/ INCLUDE_FILES)

# Список модулей для линковки
set(LINK_LIBS module_example_3)

# Добавить в сборку статическую библиотеку "module_example_1":
add_library(module_example_1 STATIC ${SRC_FILES})

# Прилинковать модули из LINK_LIBS
target_link_libraries(module_example_1 ${LINK_LIBS})

# Внутри модуля подключение заголовочных файлов происходит через #include "header.h"
# Из сторонних модулей подключение происходит через #include "module_example_1/header.h"
target_include_directories(module_example_1 PRIVATE include/module_example_1)
target_include_directories(module_example_1 INTERFACE include)
