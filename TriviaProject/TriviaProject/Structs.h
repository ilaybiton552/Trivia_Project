#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"

using std::string;
using std::vector;

class IRequestHandler; // problem of circular reference

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

struct LoginRequest
{
	string username;
	string password;
};

struct SignupRequest
{
	string username;
	string password;
	string email;
	string address;
	string phoneNumber;
	string birthDate;
};

struct RequestInfo
{
	int id;
	time_t receivalTime;
	vector<unsigned char> buffer;
};

struct RequestResult
{
	vector<unsigned char> response;
	IRequestHandler* newHandler;
};