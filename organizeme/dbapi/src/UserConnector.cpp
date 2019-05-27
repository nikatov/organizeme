#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <clocale>
#include <stdio.h>

#include "package/changeuser.h"
#include "userconnector.h"

tuple UserConnector::getSqlParameters(ChangeUser &user){
  tuple t;
  t += setField("username", user.getUsername(), text);
  t += setField("first_name", user.getFirstName(), text);
  t += setField("last_name", user.getLastName(), text);
  t += setField("patronymic", user.getPatronymic(), text);
  t += setField("password", user.getPassword(), text);
  t.delLastComma();
  return t;
}

uint UserConnector::createUser(ChangeUser &user) {
  if(!user.getUsername().empty() && !user.getFirstName().empty() && !user.getLastName().empty() && !user.getPassword().empty()) {
    tuple t = getSqlParameters(user);
    pqxx::result r = txn.exec(str("INSERT INTO users (") + t.fields + str(") VALUES (") + t.parameters + str(") RETURNING id"));
    return std::atoi(r[0][0].c_str());
  }
  std::cout << "Error. Какое-то из необходимых полей пустое" << std::endl;
  return 0;
}

void UserConnector::updateUser(ChangeUser &user) {
  if(user.getId() > 0){
    tuple t = getSqlParameters(user);
    pqxx::result r = txn.exec(str("UPDATE users SET (") + t.fields + str(") = (") + t.parameters + str(") WHERE id = ") + std::to_string(user.getId()));
  }
  else{
    std::cout << "Error. Передан id < 0" << std::endl;
  }
}

void UserConnector::deleteUser(ChangeUser &user) {
  pqxx::result r = txn.exec("DELETE FROM users WHERE id = " + txn.quote(user.getId()));
}

pqxx::result UserConnector::getUserGroupsFromUser(ChangeUser &user) {
  return txn.exec("SELECT * FROM user_user_group WHERE id_user = " + txn.quote(user.getId()));
}
