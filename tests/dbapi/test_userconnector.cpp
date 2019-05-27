#include <iostream>
#include <pqxx/pqxx>
#include <iostream>

#include "dbapi/userconnector.h"
#include "package/changeuser.h"

int main(int, char *argv[])
{
  try
  {
    pqxx::connection c{"dbname=organizeme user=destr0y"};
    UserConnector userConnector(c);

    ChangeUser user1;
    user1.setUsername("pro100max");
    user1.setFirstName("Max");
    user1.setLastName("Ivanov");
    user1.setPassword("password");

    uint userId = userConnector.createUser(user1);
    user1.setId(userId);

    ChangeUser user2;
    user2.setId(user1.getId());
    user2.setPatronymic("Andreevich");
    user2.setPassword("iChangedPassword!");

    userConnector.updateUser(user2);

    userConnector.deleteUser(user2);

    userConnector.commit();

    std::cout << "Seccess!" << std::endl;
  }
  catch (const pqxx::sql_error &e)
  {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return 5;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 6;
  }
}
