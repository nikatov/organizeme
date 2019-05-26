#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "TaskGroupConnector.h"
#include "package/changetaskgroup.h"

TaskGroupConnector::tuple TaskGroupConnector::getSqlParameters(ChangeTaskGroup &task){
    std::string parameters;
    std::string fields;
    if(task.getIdUserGroup() > 0){
      fields += "id_user_group, ";
      parameters += std::to_string(task.getIdUserGroup()) + ", ";
    }
    if(!task.getName().empty()){
        fields += "name, ";
        parameters += "'" + task.getName() + "', ";
    }
    fields.erase(fields.end()-2, fields.end());
    parameters.erase(parameters.end()-2, parameters.end());
    tuple t(fields, parameters);
    return t;
}

std::string TaskGroupConnector::stringWrapper(uint64_t &obj, enum fieldType type) {
  if(timestamp == type) {
    return str(", timestamp '1970/01/01' + interval '") + std::to_string(obj) + str(" second'");
  }
  else if(interval == type) {
    return str(", '") + std::to_string(obj) + str(" second'");
  }
  return str(", ") + std::to_string(obj);
}

std::string TaskGroupConnector::stringWrapper(std::string &obj, fieldType type) {
  return str(", '") + str(obj) + str("'");
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
