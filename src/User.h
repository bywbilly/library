// User.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include <string>

class User
{
public:
	User(std::string const &username, std::string const &password);
	virtual ~User();

	virtual std::string getUsername() const;
	virtual std::string getPassword() const;
	virtual void setPassword(std::string const &);

private:
    std::string Password;
    std::string Username;
};
