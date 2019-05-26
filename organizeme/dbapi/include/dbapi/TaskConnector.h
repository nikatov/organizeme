#include <pqxx/pqxx>

#include "package/changetask.h"

#define str std::string

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

  tuple getSqlParameters(ChangeTask &task);
  std::string stringWrapper(uint64_t &obj, fieldType type);
  std::string stringWrapper(std::string &obj, fieldType type);

  pqxx::work txn;
};
