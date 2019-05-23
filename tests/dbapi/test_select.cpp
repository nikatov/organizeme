#include <iostream>
#include <pqxx/pqxx>

#include "dbapi/select.h"
/// Query employees from database, print results.
int main(int, char *argv[])
{
  try
  {
    pqxx::result r = selectTasksFromTaskGroupId(1);

    // Results can be accessed and iterated again.  Even after the connection
    // has been closed.
    for (auto row: r)
    {
      std::cout << "Row: ";
      // Iterate over fields in a row.
      for (auto field: row) std::cout << field.c_str() << " ";
      std::cout << std::endl;
    }
  }
  catch (const pqxx::sql_error &e)
  {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    return 2;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
