cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(organizeme VERSION 0.0.1 LANGUAGES CXX)

# Установка переменных CMake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Проталкивание типа сборки в директиву препроцессора через шаблон config.h.in
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
  option(DEBUG_MODE "Сборка осуществляется в режиме Debug" ON)
else()
  option(DEBUG_MODE "Сборка осуществляется в режиме Debug" OFF)
endif()
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
"${CMAKE_CURRENT_SOURCE_DIR}/config.h")

# Требовать обработку файла "organizeme/CMakeFiles.txt":
add_subdirectory(organizeme)

# Добавить в сборку исполняемый файл "organizeme":
add_executable(executable_example_1 main_example_1.cpp)

# Скомпоновать исполняемый файл "organizeme" со
# скомпилированными статическими библиотеками отдельных модулей:
target_link_libraries(executable_example_1 module_example_1 module_example_2 module_example_3)

# Установить исполняемый файл "organizeme" в директорию "bin":
install(TARGETS executable_example_1 DESTINATION ${EXECUTABLE_OUTPUT_PATH})
