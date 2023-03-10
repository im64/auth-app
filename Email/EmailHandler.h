#pragma once
#include <string>

class EmailHandler
{
public:
    virtual int sendConfirmationCode(const std::string &recepient, const std::string &username, const std::string &code) = 0;
    virtual int sendPasswordRecovery(const std::string &recepient, const std::string &username, const std::string &code) = 0;
    virtual int sendRegistrationSuccessful(const std::string &recepient, const std::string &username) = 0;
    virtual int sendPasswordRecoverySuccessful(const std::string &recepient, const std::string &username) = 0;
};