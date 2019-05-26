#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "TaskConnector.h"
#include "package/changetask.h"

tuple TaskConnector::getSqlParameters(ChangeTask &task){
    std::string parameters;
    std::string fields;
    if(task.getIdGroupTask() > 0){
        fields += "id_task_group, ";
        parameters += std::to_string(task.getIdGroupTask()) + ", ";
    }
    if(task.getIdUser() > 0){
        fields += "id_user, ";
        parameters += std::to_string(task.getIdUser()) + ", ";
    }
    if(task.getIsFinished()){
        fields += "is_finished, ";
        parameters += (task.getIsFinished() ? "true, " : "false, ");
    }
    if(task.getTimePlanned() > 0){
        fields += "time_planned, ";
        parameters += "timestamp '1970/01/01' + interval '" + std::to_string(task.getTimePlanned()) + " second', ";
    }
    if(task.getTimeDoingTask() > 0){
        fields += "time_doing_task, ";
        parameters += "'" + std::to_string(task.getTimeDoingTask()) + " second', ";
    }
    if(task.getTimeDeadline() > 0){
        fields += "time_deadline, ";
        parameters += "timestamp '1970/01/01' + interval '" + std::to_string(task.getTimeDeadline()) + " second', ";
    }
    if(!task.getTitle().empty()){
        fields += "title, ";
        parameters +=  "'" + task.getTitle() + "', ";
    }
    if(!task.getDescription().empty()){
        fields += "description, ";
        parameters +=  "'" + task.getDescription() + "', ";
    }
    if(task.getPriority() > 0){
        fields += "priority, ";
        parameters += std::to_string(task.getPriority()) + ", ";
    }
    fields.erase(fields.end()-2, fields.end());
    parameters.erase(parameters.end()-2, parameters.end());
    tuple t(fields, parameters);
    return t;
}

std::string TaskConnector::stringWrapper(uint64_t &obj, enum fieldType type) {
  if(timestamp == type) {
    return str(", timestamp '1970/01/01' + interval '") + std::to_string(obj) + str(" second'");
  }
  else if(interval == type) {
    return str(", '") + std::to_string(obj) + str(" second'");
  }
  return str(", ") + std::to_string(obj);
}

std::string TaskConnector::stringWrapper(std::string &obj, fieldType type) {
  return str(", '") + str(obj) + str("'");
}

uint TaskConnector::createTask(ChangeTask &task) {
  if(task.getIdGroupTask() && task.getIdUser() && !task.getTitle().empty()) {
    tuple t = getSqlParameters(task);
    std::cout << str("INSERT INTO tasks (") + t.fields + str(") VALUES (") + t.parameters + str(")") << std::endl;
    pqxx::result r = txn.exec(str("INSERT INTO tasks (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
    return std::atoi(r[0][0].c_str());
  }
  return 0;
}

void TaskConnector::updateTask(ChangeTask &task) {
  tuple t = getSqlParameters(task);
  std::cout << str("UPDATE tasks SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(task.getId()) << std::endl;
  pqxx::result r = txn.exec(str("UPDATE tasks SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(task.getId()));
}

void TaskConnector::deleteTask(ChangeTask &task) {
  pqxx::result r = txn.exec("DELETE FROM tasks WHERE id = " + txn.quote(task.getId()));
}

pqxx::result TaskConnector::getTasksFromTaskGroupId(const int taskGroupId) {
  return txn.exec("SELECT * FROM tasks WHERE id_task_group = " + txn.quote(taskGroupId));
}
