#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "UserGroupConnector.h"
#include "package/changeusergroup.h"

UserGroupConnector::tuple UserGroupConnector::getSqlParameters(ChangeUserGroup &userGroup){
    std::string parameters;
    std::string fields;
    if(!userGroup.getGroupName().empty()){
        fields += "name, ";
        parameters += "'" + str(userGroup.getGroupName()) + "', ";
    }
    fields.erase(fields.end()-2, fields.end());
    parameters.erase(parameters.end()-2, parameters.end());
    tuple t(fields, parameters);
    return t;
}

std::string UserGroupConnector::stringWrapper(uint64_t &obj, enum fieldType type) {
  if(timestamp == type) {
    return str(", timestamp '1970/01/01' + interval '") + std::to_string(obj) + str(" second'");
  }
  else if(interval == type) {
    return str(", '") + std::to_string(obj) + str(" second'");
  }
  return str(", ") + std::to_string(obj);
}

std::string UserGroupConnector::stringWrapper(std::string &obj, fieldType type) {
  return str(", '") + str(obj) + str("'");
}

uint UserGroupConnector::createUserGroup(ChangeUserGroup &userGroup) {
  if(!userGroup.getGroupName().empty()) {
    tuple t = getSqlParameters(userGroup);
    std::cout << str("INSERT INTO user_groups (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id") << std::endl;
    pqxx::result r = txn.exec(str("INSERT INTO user_groups (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
    return std::atoi(r[0][0].c_str());
  }
  std::cout << "Какое-то из необходимых полей пустое" << std::endl;
  return 0;
}

void UserGroupConnector::updateUserGroup(ChangeUserGroup &userGroup) {
  if(userGroup.getId() > 0){
    tuple t = getSqlParameters(userGroup);
    std::cout << str("UPDATE user_groups SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(userGroup.getId()) << std::endl;
    pqxx::result r = txn.exec(str("UPDATE user_groups SET (") + t.fields + str(") = ROW(") + t.parameters + str(") WHERE id = ") + std::to_string(userGroup.getId()));
  }
  else{
    std::cout << "Передан id < 0" << std::endl;
  }
}

void UserGroupConnector::deleteUserGroup(ChangeUserGroup &userGroup) {
  std::cout << "DELETE FROM user_groups WHERE id = " + txn.quote(userGroup.getId()) << std::endl;
  pqxx::result r = txn.exec("DELETE FROM user_groups WHERE id = " + txn.quote(userGroup.getId()));
}
