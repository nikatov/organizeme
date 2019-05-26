#include <pqxx/pqxx>

#include "package/changeuser.h"

#define str std::string

class UserConnector {
public:
  UserConnector(pqxx::connection &c) : txn({c}) {}
  ~UserConnector() {}

  uint createUser(ChangeUser &user);
  void updateUser(ChangeUser &user);
  void deleteUser(ChangeUser &user);
  pqxx::result getUsersFromUserGroupId(const int taskGroupId);
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

  tuple getSqlParameters(ChangeUser &user);
  std::string stringWrapper(uint64_t &obj, fieldType type);
  std::string stringWrapper(std::string &obj, fieldType type);

  pqxx::work txn;
};
