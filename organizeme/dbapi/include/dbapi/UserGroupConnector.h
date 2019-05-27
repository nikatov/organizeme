#pragma once

#include <pqxx/pqxx>

#include "package/changeusergroup.h"
#include "core.h"

class UserGroupConnector {
public:
  UserGroupConnector(pqxx::connection &c) : txn({c}) {}
  ~UserGroupConnector() {}

  uint createUserGroup(ChangeUserGroup &userGroup);
  void updateUserGroup(ChangeUserGroup &userGroup);
  void deleteUserGroup(ChangeUserGroup &userGroup);

  void commit() { txn.commit(); }
private:

  tuple getSqlParameters(ChangeUserGroup &userGroup);

  pqxx::work txn;
};
