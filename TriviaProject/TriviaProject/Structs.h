#pragma once
#include <string>

using std::string;

struct ErrorResponse
{
	string message;
};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};