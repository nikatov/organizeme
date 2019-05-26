#include <iostream>
#include <pqxx/pqxx>
#include <iostream>

#include "dbapi/TaskConnector.h"
#include "package/changetask.h"

int main(int, char *argv[])
{
  try
  {
    uint taskGroupId = 1;

    ChangeTask task1(1, 1, 1, false, 0, 672, 0, "Hello", "world", 1);
    ChangeTask task2(1, 1, 1, true, 1558823076, 1000, 1558823076, "Hello", "New World!!1!", 5);

    pqxx::connection c{"dbname=organizeme user=destr0y"};
    TaskConnector taskConnector(c);

    pqxx::result r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    uint beforeSize = r.size();
    for (auto field: r.end()-1) std::cout << field.c_str() << " ";
    std::cout << std::endl;

    uint taskId = taskConnector.createTask(task1);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    if (taskId != std::atoi((r.end()-1)[0].c_str())) {
      std::cout << "Id возвращенное createTask не равняется реальному" << std::endl;
      return 1;
    }

    uint afterSize = r.size();
    if (afterSize - beforeSize != 1){
      std::cout << "количество строк не увеличелось на 1 после добавления" << std::endl;
      return 2;
    }
    for (auto field: r.end()-1) std::cout << field.c_str() << " ";
    std::cout << std::endl;
    // убедиться, что в последней строке именно тот changeTask который мы подали на вход

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
