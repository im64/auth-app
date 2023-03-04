#pragma once
#include <string>

class DatabaseHandler
{
    virtual int createUser() = 0;
    virtual int validateCredentials() = 0;
    virtual int isEmailPresent() = 0;
    virtual int createUser() = 0;
};