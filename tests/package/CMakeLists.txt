set(TEST_SRC test_package.cpp)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

# Добавить в сборку исполняемый файл:
add_executable(test_package test_package.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(test_package package ${Boost_LIBRARIES})
target_include_directories(test_package PRIVATE ${Boost_INCLUDE_DIR})
# Установить исполняемый файл в директорию "bin":
install(TARGETS test_package DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
