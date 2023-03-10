#include "EmailHandlerImpl.h"

#include <quickmail.h>
#include <string>
#include <fstream>
#include <iostream>

namespace
{
    std::string fileToString(const std::string &path)
    {
        std::ifstream file(path.c_str());
        if (!file.is_open())
        {
            std::cerr << "Can't open file: " << path << std::endl;
        }
        std::string res((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
        file.close();
        return res;
    }

    void replaceWord(std::string &text, const std::string &wordToReplace, const std::string &newWord)
    {
        size_t pos = text.find(wordToReplace, 0);
        if (pos != std::string::npos)
            text.replace(pos, wordToReplace.length(), newWord);

        // size_t pos = text.find(wordToReplace, 0);
        // if (pos != std::string::npos)
        //     text.replace(pos, wordToReplace.length(), newWord);
    }
}

EmailHandlerImpl::EmailHandlerImpl(const std::string &filepath)
{
    std::string credentials = fileToString(filepath);
    auto delimPos = credentials.find(':');
    login = credentials.substr(0, delimPos);
    password = credentials.substr(delimPos + 1, credentials.length() - delimPos);
}

int EmailHandlerImpl::sendEmail(const std::string &body, const std::string &recepient, const std::string &subject)
{
    quickmail_initialize();

    quickmail mailobj = quickmail_create(login.c_str(), subject.c_str());
    quickmail_add_to(mailobj, recepient.c_str());
    quickmail_add_body_memory(mailobj, "text/html", const_cast<char *>(body.c_str()), body.length(), 0);

    const char *errmsg = quickmail_send_secure(mailobj, "smtp.gmail.com", 465, login.c_str(), password.c_str());

    quickmail_destroy(mailobj);
    quickmail_cleanup();
    return errmsg == 0;
}

int EmailHandlerImpl::sendConfirmationCode(const std::string &recepient, const std::string &username, const std::string &code)
{
    auto body = fileToString("Email/Letters/confirmationCode.html");
    replaceWord(body, "USERNAME", username);
    replaceWord(body, "CODE", code);

    std::string subject{"Please confirm your email"};
    return sendEmail(body, recepient, subject);
}

int EmailHandlerImpl::sendPasswordRecovery(const std::string &recepient, const std::string &username, const std::string &code)
{
    auto body = fileToString("Email/Letters/passwordRecovery.html");
    replaceWord(body, "USERNAME", username);
    replaceWord(body, "CODE", code);
    std::string subject{"Password Recovery"};
    return sendEmail(body, recepient, subject);
}

int EmailHandlerImpl::sendRegistrationSuccessful(const std::string &recepient, const std::string &username)
{
    std::cout << username << std::endl;
    std::string body = fileToString("Email/Letters/registrationSuccessful.html");
    std::cout << body << std::endl;
    replaceWord(body, "USERNAME", username);

    std::cout << "*****************************" << std::endl;
    std::cout << body << std::endl;

    std::string subject{"Registration Successful!"};
    return sendEmail(body, recepient, subject);
}

int EmailHandlerImpl::sendPasswordRecoverySuccessful(const std::string &recepient, const std::string &username)
{
    auto body = fileToString("Email/Letters/passwordChanged.html");
    replaceWord(body, "USERNAME", username);
    std::string subject{"Password Successfully changed!"};
    return sendEmail(body, recepient, subject);
}