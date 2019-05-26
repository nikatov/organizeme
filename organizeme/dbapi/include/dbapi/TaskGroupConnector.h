#include <pqxx/pqxx>

#include "package/changetaskgroup.h"

#define str std::string

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

  tuple getSqlParameters(ChangeTaskGroup &task);
  std::string stringWrapper(uint64_t &obj, fieldType type);
  std::string stringWrapper(std::string &obj, fieldType type);

  pqxx::work txn;
};
