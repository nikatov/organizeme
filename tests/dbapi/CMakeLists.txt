set(TEST_SRC test_dbapi.cpp)


# Добавить тесты:
add_executable(test_taskconnector test_taskconnector.cpp)

target_link_libraries(test_taskconnector dbapi package)
target_include_directories(test_taskconnector PRIVATE ${PQXX_INCLUDE_DIRECTORIES})

install(TARGETS test_taskconnector DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)



# Добавить тесты:
add_executable(test_taskgroupconnector test_taskgroupconnector.cpp)

target_link_libraries(test_taskgroupconnector dbapi package)
target_include_directories(test_taskgroupconnector PRIVATE ${PQXX_INCLUDE_DIRECTORIES})

install(TARGETS test_taskgroupconnector DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)



# Добавить тесты:
add_executable(test_userconnector test_userconnector.cpp)

target_link_libraries(test_userconnector dbapi package)
target_include_directories(test_userconnector PRIVATE ${PQXX_INCLUDE_DIRECTORIES})

install(TARGETS test_userconnector DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)



# Добавить тесты:
add_executable(test_usergroupconnector test_usergroupconnector.cpp)

target_link_libraries(test_usergroupconnector dbapi package)
target_include_directories(test_usergroupconnector PRIVATE ${PQXX_INCLUDE_DIRECTORIES})

install(TARGETS test_usergroupconnector DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
