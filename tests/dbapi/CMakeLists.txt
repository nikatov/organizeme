set(TEST_SRC test_select.cpp)

# Указать директории хэдеров:
find_package(PQXX)
include_directories(${PQXX_INCLUDE_DIRECTORIES})

# Добавить в сборку исполняемый файл:
add_executable(test_select test_select.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(test_select dbapi pqxx)
# Установить исполняемый файл в директорию "bin":
install(TARGETS test_select DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
