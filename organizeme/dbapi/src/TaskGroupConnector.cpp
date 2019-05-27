#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "package/changetaskgroup.h"
#include "taskgroupconnector.h"

tuple TaskGroupConnector::getSqlParameters(ChangeTaskGroup &task){
    tuple t;
    t += setField("id_user_group", task.getIdUserGroup(), integer);
    t += setField("name", task.getName(), text);
    t.delLastComma();
    return t;
}

uint TaskGroupConnector::createTaskGroup(ChangeTaskGroup &task) {
  tuple t = getSqlParameters(task);
  pqxx::result r = txn.exec(str("INSERT INTO task_groups (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
  return  std::atoi(r[0][0].c_str());
}

void TaskGroupConnector::updateTaskGroup(ChangeTaskGroup &task) {
  tuple t = getSqlParameters(task);
  pqxx::result r = txn.exec(str("UPDATE task_groups SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(task.getId()));
}

void TaskGroupConnector::deleteTaskGroup(ChangeTaskGroup &task) {
  pqxx::result r = txn.exec("DELETE FROM task_groups WHERE id = " + txn.quote(task.getId()));
}

pqxx::result TaskGroupConnector::getTasksFromTaskGroup(ChangeTaskGroup &taskGroup) {
  if(taskGroup.getId() > 0){
    return txn.exec("SELECT * FROM tasks WHERE id_task_group = " + txn.quote(taskGroup.getId()));
  }
  std::cout << "Error. task.Group.id должен быть больше нуля" << std::endl;
  return pqxx::result();
}
