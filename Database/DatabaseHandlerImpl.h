#pragma once

#include <sqlite3.h>

#include "DatabaseHandler.h"

class DatabaseHandlerImpl final : public DatabaseHandler
{
public:
    explicit DatabaseHandlerImpl(const std::string &dbPath);
    virtual ~DatabaseHandlerImpl();

public:
    virtual int createUser(const User &user) final;
    virtual bool validateCredentials(const std::string &username, const std::string &password) final;
    virtual bool isEmailPresent(const std::string &email) final;
    virtual bool isUsernamePresent(const std::string &username) final;

private:
    sqlite3 *_databaseConn;
};