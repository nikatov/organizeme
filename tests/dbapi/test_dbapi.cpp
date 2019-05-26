#include <iostream>
#include <pqxx/pqxx>
#include <iostream>

#include "dbapi/TaskConnector.h"
#include "dbapi/TaskGroupConnector.h"
#include "dbapi/UserConnector.h"
#include "dbapi/userGroupConnector.h"
#include "package/changetask.h"
#include "package/changetaskgroup.h"
#include "package/changeuser.h"
#include "package/changeusergroup.h"

int main(int, char *argv[])
{
  int i = 0;
std::cout << i++ << std::endl;
  try
  {
    uint taskGroupId = 1;

    ChangeTask task1(1, 1, 1, false, 1, 672, 1, "Hello", "world", 1);
    ChangeTask task2(1, 1, 1, true, 1558823076, 1000, 1558823076, "Hello", "New World!!1!", 5);

    pqxx::connection c{"dbname=organizeme user=destr0y"};
    TaskConnector taskConnector(c);

    pqxx::result r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    uint beforeSize = r.size();
    for (auto field: r.end()-1) std::cout << field.c_str() << " ";
    std::cout << std::endl;

    uint taskId = taskConnector.createTask(task1);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    uint afterSize = r.size();
    if (afterSize - beforeSize != 1){
      std::cout << "количество строк не увеличелось на 1 после добавления" << std::endl;
      return 2;
    }
    for (auto field: r.end()-1) std::cout << field.c_str() << " ";
    std::cout << std::endl;
    task2.setId(taskId);
    taskConnector.updateTask(task2);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);
    beforeSize = afterSize;
    afterSize = r.size();
    if(afterSize != beforeSize){
      std::cout << "количество строк изменилось после обновления (?): " << std::endl;
      return 3;
    }
    for (auto field: r.end()-1) std::cout << field.c_str() << " ";
    std::cout << std::endl;

    taskConnector.deleteTask(task2);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);
    beforeSize = afterSize;
    afterSize = r.size();
    if(beforeSize - afterSize != 1) {
      std::cout << "количество строк убавилось на 1(?): " << std::endl;
      return 4;
    }
    for (auto field: r.end()-1) std::cout << field.c_str() << " ";
    std::cout << std::endl;

    taskConnector.commit();

    ChangeTaskGroup taskGroup1;
    taskGroup1.setIdUserGroup(1);
    taskGroup1.setName("valeraaaaa");

    ChangeTaskGroup taskGroup2;
    taskGroup2.setIdUserGroup(1);
    taskGroup2.setName("Valera");

    TaskGroupConnector taskGroupConnector(c);

    uint taskGroupIdAfterCreate = taskGroupConnector.createTaskGroup(taskGroup1);
    taskGroup1.setId(taskGroupIdAfterCreate);
    taskGroup2.setId(taskGroup1.getId()); //тк 2я группа - изменение первой.

    taskGroupConnector.updateTaskGroup(taskGroup2);

    taskGroupConnector.getTasksFromTaskGroup(taskGroup2);

    taskGroupConnector.deleteTaskGroup(taskGroup2);

    taskGroupConnector.commit();

    UserConnector userConnector(c);

    ChangeUser user1;
    user1.setUsername("pro100max");
    user1.setFirstName("Max");
    user1.setLastName("Ivanov");
    user1.setPassword("password");

    uint userId = userConnector.createUser(user1);
    user1.setId(userId);

    ChangeUser user2;
    user2.setId(user1.getId());
    user2.setPatronymic("Andreevich");
    user2.setPassword("iChangedPassword!");

    userConnector.updateUser(user2);

    userConnector.deleteUser(user2);

    userConnector.commit();

    UserGroupConnector userGroupConnector(c);

    ChangeUserGroup userGroup1;
    userGroup1.setGroupName("Название новой группы");

    uint userGroupId = userGroupConnector.createUserGroup(userGroup1);
    userGroup1.setId(userGroupId);

    ChangeUserGroup userGroup2;
    userGroup2.setGroupName("А это НОВОЕ название новой группы");
    userGroup2.setId(userGroup1.getId());

    userGroupConnector.updateUserGroup(userGroup2);

    userGroupConnector.deleteUserGroup(userGroup2);
    userGroupConnector.commit();
  }
  catch (const pqxx::sql_error &e)
  {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return 5;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 6;
  }
}
