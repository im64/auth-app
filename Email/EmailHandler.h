#pragma once
#include <string>

class EmailHandler
{
public:
    virtual int sendConfirmation(const std::string& email) = 0;
    virtual int sendPasswordRecovery(const std::string& email) = 0;
    virtual int sendRegistrationSuccessful(const std::string& email) = 0;
    virtual int sendPasswordRecoverySuccessful(const std::string& email) = 0;
};