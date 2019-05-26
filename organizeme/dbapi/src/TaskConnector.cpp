#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "TaskConnector.h"
#include "package/changetask.h"

#define str std::string

// char fields[9][20] = { "id_task_group", "id_user", "is_finished", "time_planned", "time_doing_task", "time_deadline", "title", "description", "priority"};
std::vector<std::string> fields({"id_task_group", "id_user", "is_finished", "time_planned", "time_doing_task", "time_deadline", "title", "description", "priority"});

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
  std::string fields2 = "id_task_group, id_user, id_place, title";
  std::string parameters = std::to_string(task.getIdGroupTask()) + str(", ")
                         + std::to_string(task.getIdUser()) + str(", 1, '") + task.getTitle() + str("'");

  uint64_t timePlanned = task.getTimePlanned();
  uint64_t timeDoingTask = task.getTimeDoingTask();
  uint64_t timeDeadline = task.getTimeDeadline();
  str description = task.getDescription();
  uint8_t priority = task.getPriority();
  if(timePlanned){
    fields2 += str(", time_planned");
    parameters += stringWrapper(timePlanned, timestamp);
  }
  if(timeDoingTask){
    fields2 += str(", time_doing_task");
    parameters += stringWrapper(timeDoingTask, interval);
  }
  if(timeDeadline){
    fields2 += str(", time_deadline");
    parameters += stringWrapper(timeDeadline, timestamp);
  }
  if(!description.empty()){
    fields2 += str(", description");
    parameters += stringWrapper(description, text);
  }
  if(priority){
    fields2 += str(", priority");
    parameters += str(", ") + std::to_string(priority);
  }

  std::cout << str("INSERT INTO tasks (") + fields2 + str(") VALUES (") + parameters + str(")") << std::endl;

  pqxx::result r = txn.exec(str("INSERT INTO tasks (") + fields2 + str(") VALUES (") + parameters + str(") RETURNING id"));
  return std::atoi(r[0][0].c_str());
}

void TaskConnector::updateTask(ChangeTask &task) {
  // std::cout << str("UPDATE tasks SET (") + fields2 + str(") = (") + parameters + str(") WHERE id = ") + std::to_string(task.getId()) << std::endl;
  // pqxx::result r = txn.exec("UPDATE tasks set id = " + txn.quote(task.getId()));
}

void TaskConnector::deleteTask(ChangeTask &task) {
  pqxx::result r = txn.exec("DELETE FROM tasks WHERE id = " + txn.quote(task.getId()));
}

pqxx::result TaskConnector::getTasksFromTaskGroupId(const int taskGroupId) {
  return txn.exec("SELECT * FROM tasks WHERE id_task_group = " + txn.quote(taskGroupId));
}
