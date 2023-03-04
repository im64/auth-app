#pragma once
#include <string>

#include "EmailHandler.h"

class EmailHandlerImpl final : public EmailHandler
{
public:
    explicit EmailHandlerImpl(const std::string& filepath);
    virtual ~EmailHandlerImpl() = default;

public:
    virtual int sendConfirmation(const std::string& email) final;
    virtual int sendPasswordRecovery(const std::string& email) final;
    virtual int sendRegistrationSuccessful(const std::string& email) final;
    virtual int sendPasswordRecoverySuccessful(const std::string& email) final;

    int sendEmail(const std::string& body, const std::string& recepient, const std::string& subject);
private:
    std::string login{};
    std::string password{};
};