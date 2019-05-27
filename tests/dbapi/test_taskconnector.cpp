#include <iostream>
#include <pqxx/pqxx>
#include <iostream>

#include "dbapi/taskconnector.h"
#include "package/changetask.h"

int main(int, char *argv[])
{
  try
  {
    pqxx::connection c{"dbname=organizeme user=destr0y"};
    TaskConnector taskConnector(c);

    uint taskGroupId = 1;
    pqxx::result r = taskConnector.getTasksFromTaskGroupId(taskGroupId);
    uint beforeSize = r.size();

    ChangeTask task1(1, 1, 1, false, 1, 672, 1, "Hello", "world", 1);
    ChangeTask task2(1, 1, 1, true, 1558823076, 1000, 1558823076, "Hello", "New World!!1!", 5);

    uint taskId = taskConnector.createTask(task1);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    uint afterSize = r.size();
    if (afterSize - beforeSize != 1){
      std::cout << "Error. количество строк не увеличелось на 1 после добавления" << std::endl;
      return 2;
    }

    task2.setId(taskId);

    taskConnector.updateTask(task2);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    beforeSize = afterSize;
    afterSize = r.size();
    if(afterSize != beforeSize){
      std::cout << "Error. количество строк изменилось после обновления (?): " << std::endl;
      return 3;
    }

    taskConnector.deleteTask(task2);

    r = taskConnector.getTasksFromTaskGroupId(taskGroupId);

    beforeSize = afterSize;
    afterSize = r.size();
    if(beforeSize - afterSize != 1) {
      std::cout << "Error. количество строк убавилось на 1(?): " << std::endl;
      return 4;
    }
    taskConnector.commit();
    std::cout << "Success!" << std::endl;
  }
  catch (const pqxx::sql_error &e)
  {
    std::cerr << "Error. SQL error: " << e.what() << std::endl;
    std::cerr << "Error. Query was: " << e.query() << std::endl;
    return 5;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 6;
  }
}
