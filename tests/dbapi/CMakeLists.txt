set(TEST_SRC test_dbapi.cpp)

# Добавить в сборку исполняемый файл:
add_executable(test_dbapi test_dbapi.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:

target_link_libraries(test_dbapi dbapi package)

target_include_directories(test_dbapi PRIVATE ${PQXX_INCLUDE_DIRECTORIES})

# Установить исполняемый файл в директорию "bin":
install(TARGETS test_dbapi DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
