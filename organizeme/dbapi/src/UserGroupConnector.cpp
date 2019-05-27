#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "package/changeusergroup.h"
#include "usergroupconnector.h"
#include "core.h"

tuple UserGroupConnector::getSqlParameters(ChangeUserGroup &userGroup){
    tuple t;
    t += setField("name", userGroup.getGroupName(), text);
    t.delLastComma();
    return t;
}

uint UserGroupConnector::createUserGroup(ChangeUserGroup &userGroup) {
  if(!userGroup.getGroupName().empty()) {
    tuple t = getSqlParameters(userGroup);
    pqxx::result r = txn.exec(str("INSERT INTO user_groups (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
    return std::atoi(r[0][0].c_str());
  }
  std::cout << "Error. Какое-то из необходимых полей пустое" << std::endl;
  return 0;
}

void UserGroupConnector::updateUserGroup(ChangeUserGroup &userGroup) {
  if(userGroup.getId() > 0){
    tuple t = getSqlParameters(userGroup);
    pqxx::result r = txn.exec(str("UPDATE user_groups SET (") + t.fields + str(") = ROW(") + t.parameters + str(") WHERE id = ") + std::to_string(userGroup.getId()));
  }
  else{
    std::cout << "Error. Передан id < 0" << std::endl;
  }
}

void UserGroupConnector::deleteUserGroup(ChangeUserGroup &userGroup) {
  pqxx::result r = txn.exec("DELETE FROM user_groups WHERE id = " + txn.quote(userGroup.getId()));
}
