#pragma once
#include <string>
#include <iostream>

using std::string;

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const string username) = 0;
	virtual int doesPasswordMatch(const string username, const string password) = 0;
	virtual int addNewUser(const string username, const string password, const string email) = 0;

};

