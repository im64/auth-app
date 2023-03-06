#include <iostream>

#include <sqlite3.h>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "DatabaseHandlerImpl.h"

DatabaseHandlerImpl::DatabaseHandlerImpl(const std::string &dbPath)
{
    int openErrorCode = sqlite3_open(dbPath.c_str(), &_databaseConn);

    if (openErrorCode != 0)
    {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(_databaseConn);
        sqlite3_close(_databaseConn);
        std::exit(1);
    }

    std::string query = "CREATE TABLE IF NOT EXISTS users ("
                        "uuid TEXT PRIMARY KEY, "
                        "username TEXT NOT NULL, "
                        "email TEXT NOT NULL UNIQUE, "
                        "password_hash TEXT NOT NULL, "
                        "is_email_confirmed INTEGER NOT NULL DEFAULT 0"
                        ");";

    char *errmsg = nullptr;
    int execErrorCode = sqlite3_exec(_databaseConn, query.c_str(), nullptr, nullptr, &errmsg);
    if (execErrorCode != SQLITE_OK)
    {
        std::cerr << "Failed to create table: " << errmsg << std::endl;
        sqlite3_free(errmsg);
        sqlite3_close(_databaseConn);
        std::exit(1);
    }
}

DatabaseHandlerImpl::~DatabaseHandlerImpl()
{
    sqlite3_close(_databaseConn);
}

int DatabaseHandlerImpl::createUser(const User &user)
{
    sqlite3_stmt *stmt;

    // Create the SQL statement with placeholders for the values
    const char *sql = "INSERT INTO users (uuid, username, email, password_hash, is_email_confirmed) VALUES (?, ?, ?, ?, ?)";

    // Prepare the statement
    if (sqlite3_prepare_v2(_databaseConn, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Error preparing the statement" << std::endl;
        return 1;
    }

    // Generate uuid
    auto uuidGen = boost::uuids::random_generator();
    std::string uuid = boost::uuids::to_string(uuidGen());

    // Bind the values to the placeholders
    sqlite3_bind_text(stmt, 1, uuid.c_str(), uuid.size(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.username.c_str(), user.username.size(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, user.email.c_str(), user.email.size(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, user.passwordHash.c_str(), user.passwordHash.size(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, 0);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Error adding user" << std::endl;
        return 2;
    }

    // Clean up
    sqlite3_finalize(stmt);
    return 0;
}

bool DatabaseHandlerImpl::validateCredentials(const std::string &username, const std::string &passwordHash)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM users WHERE username = ? AND password_hash = ?";

    if (sqlite3_prepare_v2(_databaseConn, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Unable to prepare query. " << sqlite3_errmsg(_databaseConn) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, passwordHash.c_str(), passwordHash.size(), SQLITE_TRANSIENT);

    bool isValid = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return isValid;
}

// There's definetely a way to avoid code duplication here. But since it's not possible to
// bind column name as a parameter to the query, I just gonna mark this place.
// TODO:
bool DatabaseHandlerImpl::isEmailPresent(const std::string &email)
{
    sqlite3_stmt *stmt;
    bool result = false;
    const char *sql = "SELECT email FROM users WHERE email = ?";

    if (sqlite3_prepare_v2(_databaseConn, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Unable to prepare query. " << sqlite3_errmsg(_databaseConn) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), email.size(), SQLITE_TRANSIENT);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result = true;
        break;
    }

    sqlite3_finalize(stmt);
    return result;
}

bool DatabaseHandlerImpl::isUsernamePresent(const std::string &username)
{
    sqlite3_stmt *stmt;
    bool result = false;
    const char *sql = "SELECT username FROM users WHERE username = ?";

    if (sqlite3_prepare_v2(_databaseConn, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Unable to prepare following query: " << sqlite3_errmsg(_databaseConn) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_TRANSIENT);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result = true;
        break;
    }

    sqlite3_finalize(stmt);
    return result;
}