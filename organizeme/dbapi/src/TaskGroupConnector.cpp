#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "package/changetaskgroup.h"
#include "TaskGroupConnector.h"

tuple TaskGroupConnector::getSqlParameters(ChangeTaskGroup &task){
    tuple t;
    t += setField("id_user_group", task.getIdUserGroup(), integer);
    t += setField("name", task.getName(), text);
    t.delLastComma();
    return t;
}

uint TaskGroupConnector::createTaskGroup(ChangeTaskGroup &task) {
  tuple t = getSqlParameters(task);
  std::cout << str("INSERT INTO task_groups (") + t.fields + str(") VALUES (") + t.parameters + str(")") << std::endl;
  pqxx::result r = txn.exec(str("INSERT INTO task_groups (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
  std::cout << std::atoi(r[0][0].c_str()) << std::endl;
  return  std::atoi(r[0][0].c_str());
}

void TaskGroupConnector::updateTaskGroup(ChangeTaskGroup &task) {
  tuple t = getSqlParameters(task);
  std::cout << str("UPDATE task_groups SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(task.getId()) << std::endl;
  pqxx::result r = txn.exec(str("UPDATE task_groups SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(task.getId()));
}

void TaskGroupConnector::deleteTaskGroup(ChangeTaskGroup &task) {
  pqxx::result r = txn.exec("DELETE FROM task_groups WHERE id = " + txn.quote(task.getId()));
}

pqxx::result TaskGroupConnector::getTasksFromTaskGroup(ChangeTaskGroup &taskGroup) {
  if(taskGroup.getId() > 0){
    std::cout << "SELECT * FROM tasks WHERE id_task_group = " + std::to_string(taskGroup.getId()) << std::endl;
    return txn.exec("SELECT * FROM tasks WHERE id_task_group = " + txn.quote(taskGroup.getId()));
  }
  else {
    std::cout << "task.Group.id должен быть больше нуля" << std::endl;
  }
}
