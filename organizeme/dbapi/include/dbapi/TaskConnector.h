#include <pqxx/pqxx>

#include "package/changetask.h"

enum fieldType {
  integer = 0,
  boolean,
  timestamp,
  interval,
  text
};

class TaskConnector {
public:
  TaskConnector(pqxx::connection &c) : txn({c}) {}
  ~TaskConnector() { txn.commit(); }

  uint createTask(ChangeTask &task);
  void updateTask(ChangeTask &task);
  void deleteTask(ChangeTask &task);
  pqxx::result getTasksFromTaskGroupId(const int taskGroupId);

private:
  std::string stringWrapper(uint64_t &obj, fieldType type);
  std::string stringWrapper(std::string &obj, fieldType type);

  pqxx::work txn;
};
