#include <pqxx/pqxx>

#include "package/changetask.h"

#define str std::string

enum fieldType {
  integer = 0,
  boolean,
  timestamp,
  interval,
  text
};

struct tuple {
  str fields;
  str parameters;
  tuple(str f, str p) : fields(f), parameters(p) {}
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
  tuple getSqlParameters(ChangeTask &task);
  std::string stringWrapper(uint64_t &obj, fieldType type);
  std::string stringWrapper(std::string &obj, fieldType type);

  pqxx::work txn;
};
