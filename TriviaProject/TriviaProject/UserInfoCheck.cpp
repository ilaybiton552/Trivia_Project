#include "UserInfoCheck.h"

bool UserInfoCheck::checkUserInfo(const string password, const string email, const string address, const string phone_number, const string birthdate)
{
}

bool UserInfoCheck::passwordCheck(const string password)
{
	regex password_regex;
}

/// <summary>
/// the function checks if the email is in the right format
/// </summary>
/// <param name="email">the email to check</param>
/// <returns>if the email is in the right format<returns>
bool UserInfoCheck::emailCheck(const string email)
{
	regex email_regex("([A-Za-z0-9]+[._-])*[A-Za-z0-9]+@[A-Za-z0-9-]+(\.[A-Z|a-z]{2,})+"); // the regex expression
	return bool(regex_match(email.begin(), email.end(), email_regex));
}

bool UserInfoCheck::addressCheck(const string address)
{


}

bool UserInfoCheck::phoneNumberCheck(const string phone_number)
{

}

bool UserInfoCheck::birthdateCheck(const string birthdate)
{

}
