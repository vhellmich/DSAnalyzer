#include "DatabaseCommunicator.h"
#include <iostream>
#include <memory> // Include for std::shared_ptr
#include <cstdlib> 

// Constructor: Open the database
DatabaseCommunicator::DatabaseCommunicator()
    : db(nullptr) {
    this->logger = Logger::Get();

    std::string dbPath;

    const char* envDbPath = std::getenv("DS_DATABASE_PATH");
    if (envDbPath != nullptr) {
        dbPath = envDbPath;
        if (logger) logger->info("Using database path from environment: " + dbPath);
    }
    else {
        // fallback if environment variable is not set
        dbPath = "../../DSDatabase/DSDatabase.db";
        if (logger) logger->warn("Environment variable DS_DATABASE_PATH not set. Using default path: " + dbPath);
    }

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        if (logger) logger->error("Can't open database: " + std::string(sqlite3_errmsg(db)));
        sqlite3_close(db);
        db = nullptr;
    }
    else {
        if (logger) logger->info("Database opened successfully.");
    }
}

// Destructor: Close the database
DatabaseCommunicator::~DatabaseCommunicator() {
    if (db) {
        sqlite3_close(db);
        if (logger) logger->info("Database closed successfully.");
    }
}

// Execute SELECT queries
Table DatabaseCommunicator::executeQuery(const std::string& query) {
    auto results = Table(); // Create a shared_ptr for Table

    if (!db) {
        if (logger) logger->error("No database connection.");
        return results; // Return an empty shared_ptr
    }

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        if (logger) logger->error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        return results; // Return an empty shared_ptr
    }

    results = fetchResults(stmt); // Populate the Table through the shared_ptr
    sqlite3_finalize(stmt);
    return results;
}

// Fetch results from SELECT
Table DatabaseCommunicator::fetchResults(sqlite3_stmt* stmt) {
    Table results;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Row row;
        int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; ++i) {
            const char* colName = sqlite3_column_name(stmt, i);
            const unsigned char* text = sqlite3_column_text(stmt, i);
            row[colName] = text ? reinterpret_cast<const char*>(text) : "NULL";
        }

        results.push_back(row);
    }

    return results;
}

// Execute INSERT/UPDATE/DELETE (non-SELECT) queries
bool DatabaseCommunicator::executeNonQuery(const std::string& query) {
    if (!db) {
        if (logger) logger->error("No database connection.");
        return false;
    }

    char* errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        if (logger) logger->error("SQL error: " + std::string(errMsg));
        sqlite3_free(errMsg);
        return false;
    }

    if (logger) logger->info("Query executed successfully.");
    return true;
}
