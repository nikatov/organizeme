#include <iostream>
#include <pqxx/pqxx>
#include <iostream>

#include "dbapi/taskgroupconnector.h"
#include "package/changetaskgroup.h"

int main(int, char *argv[])
{
  try
  {
    pqxx::connection c{"dbname=organizeme user=destr0y"};
    TaskGroupConnector taskGroupConnector(c);

    ChangeTaskGroup taskGroup1;
    taskGroup1.setIdUserGroup(1);
    taskGroup1.setName("valeraaaaa");

    ChangeTaskGroup taskGroup2;
    taskGroup2.setIdUserGroup(1);
    taskGroup2.setName("Valera");


    uint taskGroupIdAfterCreate = taskGroupConnector.createTaskGroup(taskGroup1);
    taskGroup1.setId(taskGroupIdAfterCreate);
    taskGroup2.setId(taskGroup1.getId()); //тк 2я группа - изменение первой.

    taskGroupConnector.updateTaskGroup(taskGroup2);

    taskGroupConnector.getTasksFromTaskGroup(taskGroup2);

    taskGroupConnector.deleteTaskGroup(taskGroup2);

    taskGroupConnector.commit();

    std::cout << "Success!" << std::endl;
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
