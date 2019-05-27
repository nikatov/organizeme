#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "package/changetask.h"
#include "taskconnector.h"
#include "core.h"

tuple TaskConnector::getSqlParameters(ChangeTask &task){
    tuple t;
    t += setField("id_task_group", task.getIdGroupTask(), integer);
    t += setField("id_user", task.getIdUser(), integer);
    t += setField("is_finished", task.getIsFinished(), boolean);
    t += setField("time_planned", task.getTimePlanned(), timestamp);
    t += setField("time_doing_task", task.getTimeDoingTask(), interval);
    t += setField("time_deadline", task.getTimeDeadline(), timestamp);
    t += setField("title", task.getTitle(), integer);
    t += setField("description", task.getDescription(), integer);
    t += setField("priority", task.getPriority(), integer);
    t.delLastComma();
    return t;
}

uint TaskConnector::createTask(ChangeTask &task) {
  if(task.getIdGroupTask() && task.getIdUser() && !task.getTitle().empty()) {
    tuple t = getSqlParameters(task);
    pqxx::result r = txn.exec(str("INSERT INTO tasks (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
    return std::atoi(r[0][0].c_str());
  }
  return 0;
}

void TaskConnector::updateTask(ChangeTask &task) {
  tuple t = getSqlParameters(task);
  pqxx::result r = txn.exec(str("UPDATE tasks SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(task.getId()));
}

void TaskConnector::deleteTask(ChangeTask &task) {
  pqxx::result r = txn.exec("DELETE FROM tasks WHERE id = " + txn.quote(task.getId()));
}

pqxx::result TaskConnector::getTasksFromTaskGroupId(const int taskGroupId) {
  return txn.exec("SELECT * FROM tasks WHERE id_task_group = " + txn.quote(taskGroupId));
}
