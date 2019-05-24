set(SRC test_server.cpp)

# Добавить в сборку исполняемый файл:
# add_executable(test_server test_server.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
# target_link_libraries(test_server ${Boost_LIBRARIES})
# target_include_directories(test_server PRIVATE ${Boost_INCLUDE_DIR})
# Установить исполняемый файл в директорию "bin":
# install(TARGETS test_server DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
