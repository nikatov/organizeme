#pragma once

#include <pqxx/pqxx>

#include "package/changeuser.h"
#include "core.h"

class UserConnector {
public:
  UserConnector(pqxx::connection &c) : txn({c}) {}
  ~UserConnector() {}

  uint createUser(ChangeUser &user);
  void updateUser(ChangeUser &user);
  void deleteUser(ChangeUser &user);

  pqxx::result getUserGroupsFromUser(ChangeUser &user);

  void commit() { txn.commit(); }
private:

  tuple getSqlParameters(ChangeUser &user);

  pqxx::work txn;
};
