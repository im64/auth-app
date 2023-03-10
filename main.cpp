#include "Database/DatabaseHandlerImpl.h"
#include "Email/EmailHandlerImpl.h"
#include "Database/User.h"
#include <iostream>

int main(int argc, char **argv)
{
    DatabaseHandlerImpl db("users.db");
    User user{"Anthony", "Qwe123", "email@google.com"};
    db.createUser(user);

    // TODO: Move this stuff to test section
    std::cout << (db.isEmailPresent(user.email) ? "yes" : "no") << std::endl;
    std::cout << (db.isUsernamePresent(user.username) ? "yes" : "no") << std::endl;
    std::cout << (db.isEmailPresent("some email") ? "yes" : "no") << std::endl;
    std::cout << (db.isUsernamePresent("Tony") ? "yes" : "no") << std::endl;
    std::cout << (db.validateCredentials("Anthony", "Qwe123") ? "yes" : "no") << std::endl;
    std::cout << (db.validateCredentials("Anthy", "Qwe12") ? "yes" : "no") << std::endl;

    EmailHandlerImpl email("Email/credentials.txt");
}