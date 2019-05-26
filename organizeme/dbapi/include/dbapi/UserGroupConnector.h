#include <pqxx/pqxx>

#include "package/changeusergroup.h"

#define str std::string

class UserGroupConnector {
public:
  UserGroupConnector(pqxx::connection &c) : txn({c}) {}
  ~UserGroupConnector() {}

  uint createUserGroup(ChangeUserGroup &userGroup);
  void updateUserGroup(ChangeUserGroup &userGroup);
  void deleteUserGroup(ChangeUserGroup &userGroup);
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

  tuple getSqlParameters(ChangeUserGroup &userGroup);
  std::string stringWrapper(uint64_t &obj, fieldType type);
  std::string stringWrapper(std::string &obj, fieldType type);

  pqxx::work txn;
};
