#pragma once

#include <string>

#include "User.h"

class DatabaseHandler
{
    virtual int createUser(const User &user) = 0;
    virtual bool validateCredentials(const std::string &username, const std::string &password) = 0;
    virtual bool isEmailPresent(const std::string &email) = 0;
    virtual bool isUsernamePresent(const std::string &username) = 0;
};