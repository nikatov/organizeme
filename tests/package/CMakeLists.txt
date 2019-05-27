set(TEST_SRC test_package.cpp)

# Добавить в сборку исполняемый файл:
add_executable(test_package test_package.cpp)
add_executable(test_package_user test_package_user.cpp)
add_executable(test_package_usergroup test_package_usergroup.cpp)
add_executable(test_package_taskgroup test_package_taskgroup.cpp)
add_executable(test_package_task test_package_task.cpp)
add_executable(test_package_header test_package_header.cpp)
# Скомпоновать исполняемый файл со статическими библиотеками отдельных модулей:
target_link_libraries(test_package package ${Boost_LIBRARIES})
target_link_libraries(test_package_user package ${Boost_LIBRARIES})
target_link_libraries(test_package_usergroup package ${Boost_LIBRARIES})
target_link_libraries(test_package_taskgroup package ${Boost_LIBRARIES})
target_link_libraries(test_package_task package ${Boost_LIBRARIES})
target_link_libraries(test_package_header package ${Boost_LIBRARIES})

target_include_directories(test_package PRIVATE ${Boost_INCLUDE_DIR})
# Установить исполняемый файл в директорию "bin":
install(TARGETS test_package DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
install(TARGETS test_package_user DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
install(TARGETS test_package_usergroup DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
install(TARGETS test_package_taskgroup DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
install(TARGETS test_package_task DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
install(TARGETS test_package_header DESTINATION ${EXECUTABLE_OUTPUT_PATH}/tests)
