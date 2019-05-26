#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "UserConnector.h"
#include "package/changeuser.h"

UserConnector::tuple UserConnector::getSqlParameters(ChangeUser &user){
    std::string parameters;
    std::string fields;
    if(!user.getUsername().empty()){
        fields += "username, ";
        parameters += "'" + str(user.getUsername()) + "', ";
    }
    if(!user.getFirstName().empty()){
        fields += "first_name, ";
        parameters += "'" + str(user.getFirstName()) + "', ";
    }
    if(!user.getLastName().empty()){
        fields += "last_name, ";
        parameters += "'" + str(user.getLastName()) + "', ";
    }
    if(!user.getPatronymic().empty()){
        fields += "patronymic, ";
        parameters += "'" + str(user.getPatronymic()) + "', ";
    }
    if(!user.getPassword().empty()){
        fields += "password, ";
        parameters += "'" + str(user.getPassword()) + "', ";
    }
    fields.erase(fields.end()-2, fields.end());
    parameters.erase(parameters.end()-2, parameters.end());
    tuple t(fields, parameters);
    return t;
}

std::string UserConnector::stringWrapper(uint64_t &obj, enum fieldType type) {
  if(timestamp == type) {
    return str(", timestamp '1970/01/01' + interval '") + std::to_string(obj) + str(" second'");
  }
  else if(interval == type) {
    return str(", '") + std::to_string(obj) + str(" second'");
  }
  return str(", ") + std::to_string(obj);
}

std::string UserConnector::stringWrapper(std::string &obj, fieldType type) {
  return str(", '") + str(obj) + str("'");
}

uint UserConnector::createUser(ChangeUser &user) {
  if(!user.getUsername().empty() && !user.getFirstName().empty() && !user.getLastName().empty() && !user.getPassword().empty()) {
    tuple t = getSqlParameters(user);
    std::cout << str("INSERT INTO users (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id") << std::endl;
    pqxx::result r = txn.exec(str("INSERT INTO users (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
    return std::atoi(r[0][0].c_str());
  }
  std::cout << "Какое-то из полей пустое" << std::endl;
  return 0;
}

void UserConnector::updateUser(ChangeUser &user) {
  if(user.getId() > 0){
    tuple t = getSqlParameters(user);
    std::cout << str("UPDATE users SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(user.getId()) << std::endl;
    pqxx::result r = txn.exec(str("UPDATE users SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(user.getId()));
  }
  else{
    std::cout << "Передан id < 0" << std::endl;
  }
}

void UserConnector::deleteUser(ChangeUser &user) {
  std::cout << "DELETE FROM users WHERE id = " + txn.quote(user.getId()) << std::endl;
  pqxx::result r = txn.exec("DELETE FROM users WHERE id = " + txn.quote(user.getId()));
}

pqxx::result UserConnector::getUsersFromUserGroupId(const int userGroupId) {
  return txn.exec("SELECT * FROM users WHERE id_user_group = " + txn.quote(userGroupId));
}
