set(TEST_SRC test_package.cpp)

# Добавить в сборку исполняемый файл:
add_executable(test_package test_package.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(test_package package)
# Установить исполняемый файл в директорию "bin":
install(TARGETS test_package DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
