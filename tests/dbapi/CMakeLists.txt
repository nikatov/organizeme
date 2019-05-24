set(TEST_SRC test_select.cpp)

# Добавить в сборку исполняемый файл:
add_executable(test_select test_select.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(test_select dbapi ${PQXX_LIBRARIES})

target_include_directories(test_select PRIVATE ${PQXX_INCLUDE_DIRECTORIES})
# Установить исполняемый файл в директорию "bin":
install(TARGETS test_select DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
