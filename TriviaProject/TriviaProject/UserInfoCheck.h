#pragma once
#include <regex>
#include <string>

using std::string;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::smatch;

class UserInfoCheck
{
public:
	static bool checkUserInfo(const string password, const string email, const string address, const string phone_number, const string birthdate);

private:
	static bool passwordCheck(const string password);
	static bool emailCheck(const string email);
	static bool addressCheck(const string address);
	static bool phoneNumberCheck(const string phoneNumber);
	static bool birthdateCheck(const string birthdate);
};

