#include <iostream>
#include <pqxx/pqxx>
#include <iostream>

#include "dbapi/usergroupconnector.h"
#include "package/changeusergroup.h"

int main(int, char *argv[])
{
  try
  {
    pqxx::connection c{"dbname=organizeme user=destr0y"};
    UserGroupConnector userGroupConnector(c);

    ChangeUserGroup userGroup1;
    userGroup1.setGroupName("Название новой группы");

    uint userGroupId = userGroupConnector.createUserGroup(userGroup1);
    userGroup1.setId(userGroupId);

    ChangeUserGroup userGroup2;
    userGroup2.setGroupName("А это НОВОЕ название новой группы");
    userGroup2.setId(userGroup1.getId());

    userGroupConnector.updateUserGroup(userGroup2);

    userGroupConnector.deleteUserGroup(userGroup2);
    userGroupConnector.commit();

    std::cout << "Success!" << std::endl;
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
