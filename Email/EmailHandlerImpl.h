#pragma once
#include <string>

#include "EmailHandler.h"

class EmailHandlerImpl final : public EmailHandler
{
public:
    explicit EmailHandlerImpl(const std::string &filepath);
    virtual ~EmailHandlerImpl() = default;

public:
    virtual int sendConfirmationCode(const std::string &recepient, const std::string& username, const std::string& code) final;
    virtual int sendPasswordRecovery(const std::string &recepient, const std::string &username, const std::string &code) final;
    virtual int sendRegistrationSuccessful(const std::string &email, const std::string &username) final;
    virtual int sendPasswordRecoverySuccessful(const std::string &email, const std::string &username) final;

    int sendEmail(const std::string &body, const std::string &recepient, const std::string &subject);

private:
    std::string login{};
    std::string password{};
};