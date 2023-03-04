#include "Email/EmailHandlerImpl.h"

int main(int argc, char **argv)
{
    EmailHandlerImpl email("Email/credentials.txt");
    email.sendRegistrationSuccessful("ilya.mikhailov4@gmail.com");
}