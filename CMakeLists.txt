cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(organizeme VERSION 0.0.1 LANGUAGES CXX)

# Установка переменных CMake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wwritable-strings")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost 1.40 COMPONENTS thread REQUIRED)
find_package(PQXX)

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
add_subdirectory(tests)
