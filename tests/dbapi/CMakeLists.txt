set(TEST_SRC test_TaskConnector.cpp)

# Добавить в сборку исполняемый файл:
add_executable(test_TaskConnector test_TaskConnector.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:

target_link_libraries(test_TaskConnector dbapi package)

target_include_directories(test_TaskConnector PRIVATE ${PQXX_INCLUDE_DIRECTORIES})

# Установить исполняемый файл в директорию "bin":
install(TARGETS test_TaskConnector DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
