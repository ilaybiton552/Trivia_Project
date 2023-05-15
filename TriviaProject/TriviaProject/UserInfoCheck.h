#pragma once
#include <regex>
#include <string>

using std::string;
using std::regex;
using std::regex_match;

class UserInfoCheck
{
public:
	static bool checkUserInfo(const string password, const string email, const string address, const string phone_number, const string birthdate);

private:
	bool passwordCheck(const string password);
	bool emailCheck(const string email);
	bool addressCheck(const string address);
	bool phoneNumberCheck(const string phone_number);
	bool birthdateCheck(const string birthdate);
};

