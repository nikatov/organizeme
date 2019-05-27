#pragma once

#include <pqxx/pqxx>

#include "package/changetask.h"
#include "core.h"

class TaskConnector {
public:
  TaskConnector(pqxx::connection &c) : txn({c}) {}
  ~TaskConnector() {}

  uint createTask(ChangeTask &task);
  void updateTask(ChangeTask &task);
  void deleteTask(ChangeTask &task);

  pqxx::result getTasksFromTaskGroupId(const int taskGroupId);

  void commit() { txn.commit(); }
private:

  tuple getSqlParameters(ChangeTask &task);

  pqxx::work txn;
};
