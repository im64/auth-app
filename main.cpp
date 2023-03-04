#include "Email/EmailHandlerImpl.h"

int main(int argc, char **argv)
{
    EmailHandlerImpl email("Email/gmail-credentials.txt");
    email.sendPasswordRecovery("ilya.mikhailov4@gmail.com");
}