#pragma once
#include <regex>
#include <string>
#include "Structs.h"

using std::string;
using std::regex;

class UserInfoCheck
{
public:
	static bool checkUserInfo(const string password, const string email, const string address, const string phone_number, const string birthdate);

private:
	bool password_check(const string password);
};

