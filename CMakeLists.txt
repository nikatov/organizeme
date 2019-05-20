cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(organizeme VERSION 0.0.1 LANGUAGES CXX)

# Установка переменных CMake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
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

# Добавить в сборку исполняемый файл:
add_executable(package_test main.cpp)

# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(package_test package)

# Установить исполняемый файл в директорию "bin":
install(TARGETS package_test DESTINATION ${EXECUTABLE_OUTPUT_PATH})
