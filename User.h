#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

struct User
{
    std::string username;
    std::string password;
    std::string email;
    boost::uuids::uuid userID = boost::uuids::random_generator()();
    bool isEmailConfirmed = false;
};