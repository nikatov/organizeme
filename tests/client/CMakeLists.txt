set(TEST_SRC test_client.cpp)

# Указать директории хэдеров:

# Добавить в сборку исполняемый файл:
add_executable(test_client test_client.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(test_client client)
# Установить исполняемый файл в директорию "bin":
install(TARGETS test_client DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
