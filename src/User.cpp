// User.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "User.h"

User::User(std::string const &username, std::string const &password)
{
    Username = username;
    Password = password;
}

User::~User()
{

}

std::string User::getUsername() const
{
    return Username;
}

std::string User::getPassword() const
{
    return Password;
}

void User::setPassword(std::string const &password)
{
    Password = password;
}

