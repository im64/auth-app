#pragma once
#include <string>

class RegistrationManager
{
public:
    int registerUser(const std::string& email, const std::string& username, const std::string& password);
    int validateUser(size_t userId);
    
private:
    bool isEmailTaken(const std::string& email);
    bool isUsernameTaken(const std::string& username);
    bool isPasswordStrong(const std::string& password);
    //database handler 
};