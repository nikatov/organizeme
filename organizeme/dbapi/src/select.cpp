#include <iostream>
#include <pqxx/pqxx>

pqxx::result selectTasksFromTaskGroupId(const int taskGroupId)
{
  pqxx::connection c{"dbname=organizeme user=destr0y"};
  pqxx::work txn{c};

  pqxx::result r = txn.exec("SELECT * FROM tasks WHERE id_task_group = " + txn.quote(taskGroupId));
  for (auto row: r) {
    for (auto elem: row) {
      std::cout << elem.c_str() << " ";
      // Address column by name.  Use c_str() to get C-style string.
      // << row["model"].c_str()
      // << " makes "
      // Address column by zero-based index.  Use as<int>() to parse as int.
      // << row[1].as<int>()
      // << "."
      // << std::endl;
    }
    std::cout << std::endl;
  }
  // Not really needed, since we made no changes, but good habit to be
  // explicit about when the transaction is done.
  txn.commit();

  // Connection object goes out of scope here.  It closes automatically.
  return r;
}
