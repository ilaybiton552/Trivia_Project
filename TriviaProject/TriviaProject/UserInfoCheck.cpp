#include "UserInfoCheck.h"
#include "UserInfoCheck.h"

/// <summary>
/// the fucntion checks if all the user information is in the wanted format
/// </summary>
/// <param name="username">string, the username</param>
/// <param name="password">the password</param>
/// <param name="email">the email</param>
/// <param name="address">the address</param>
/// <param name="phone_number">the phone number</param>
/// <param name="birthdate">the birthdate</param>
/// <returns>if all the user information is in the wanted format</returns>
bool UserInfoCheck::checkUserInfo(const string username, const string password, const string email, const string address, const string phone_number, const string birthdate)
{
	return(usernameCheck(username) && passwordCheck(password) && emailCheck(email) && 
		addressCheck(address) && phoneNumberCheck(phone_number), birthdateCheck(birthdate));
}

/// <summary>
/// Checks if the username is valid
/// </summary>
/// <param name="username">string, the username</param>
/// <returns>bool, if the username is valid</returns>
bool UserInfoCheck::usernameCheck(const string username)
{
	smatch m;
	return (username.size() <= 12 && regex_search(username, m, regex("[a-zA-Z]")));
}

/// <summary>
/// the function checks if the password is in the right format
/// </summary>
/// <param name="password">the password to check</param>
/// <returns>if the password is in the right format</returns>
bool UserInfoCheck::passwordCheck(const string password)
{
	smatch m;
	if (password.size() != 8) // check if the password lenght is 8
	{
		return false;
	}
	else if (!regex_search(password, m, regex("[a-z]"))) // search lowercase letter
	{
		return false;
	}
	else if (!regex_search(password, m, regex("[A-Z]"))) // search uppercase letter
	{
		return false;
	}
	else if (!regex_search(password, m, regex("[0-9]"))) // search digit
	{
		return false;
	}
	else if (!regex_search(password, m, regex("[!@#$%^&*]"))) // search special char
	{
		return false;
	}
	return true;
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

/// <summary>
/// the function checks if the address is in the right format
/// </summary>
/// <param name="address">the address to check</param>
/// <returns>if the address is in the right format</returns>
bool UserInfoCheck::addressCheck(const string address)
{
	regex address_regex("([A-Za-z])*[, ]+([0-9])*[, ]+([A-Za-z]+)"); // the regex expression
	return bool(regex_match(address.begin(), address.end(), address_regex));
}

/// <summary>
/// the function checks if the phone number is in the right format
/// </summary>
/// <param name="phoneNumber">the phone number to check</param>
/// <returns>if the phone number is in the format</returns>
bool UserInfoCheck::phoneNumberCheck(const string phoneNumber)
{
	regex phone_number_regex1("0+([0-9]){8}"); // first regex expression
	regex phone_number_regex2("05+([0-9]){8}"); // second regex expresssion
	return bool(regex_match(phoneNumber.begin(), phoneNumber.end(), phone_number_regex1) || regex_match(phoneNumber.begin(), phoneNumber.end(), phone_number_regex2));
}

/// <summary>
/// the function checks if the birthdate is in the right format
/// </summary>
/// <param name="birthdate">the birthdate to check</param>
/// <returns>if the birthdate is in the right format</returns>
bool UserInfoCheck::birthdateCheck(const string birthdate)
{
	regex birthdate_regex("^(3[01]|[12][0-9]|0[1-9]).(1[0-2]|0[1-9]).(19\d\d|20[01]\d)$"); // the regex expression
	return bool(regex_match(birthdate.begin(), birthdate.end(), birthdate_regex));
}

