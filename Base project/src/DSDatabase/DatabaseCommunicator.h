#ifndef DATABASECOMUNICATOR_H_ 
#define DATABASECOMUNICATOR_H_

#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "../Logger.h"

using Row = std::map<std::string, std::string>;
using Table = std::vector<Row>;

/// <summary>
/// Used to communicate with the SQLite database.
/// It can not communicate with other databases other than DSDatabase.db in the same directory.
/// It is not a general purpose database communicator. 
/// Will be changed to a more general purpose database communicator in the future.
/// </summary>
class DatabaseCommunicator {
public:
	DatabaseCommunicator();
	~DatabaseCommunicator();

	// Read operations
	Table executeQuery(const std::string& query);

	// Write operations
	bool executeNonQuery(const std::string& query);


private:
	sqlite3* db;
	std::shared_ptr<spdlog::logger> logger;

	Table fetchResults(sqlite3_stmt* stmt);

};

#endif
