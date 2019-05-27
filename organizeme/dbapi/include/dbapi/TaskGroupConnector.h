#pragma once

#include <pqxx/pqxx>

#include "package/changetaskgroup.h"
#include "core.h"

class TaskGroupConnector {
public:
  TaskGroupConnector(pqxx::connection &c) : txn({c}) {}
  ~TaskGroupConnector() {}

  uint createTaskGroup(ChangeTaskGroup &taskGroup);
  void updateTaskGroup(ChangeTaskGroup &taskGroup);
  void deleteTaskGroup(ChangeTaskGroup &taskGroup);

  pqxx::result getTasksFromTaskGroup(ChangeTaskGroup &taskGroup);

  void commit() { txn.commit(); }
private:

  tuple getSqlParameters(ChangeTaskGroup &task);

  pqxx::work txn;
};
