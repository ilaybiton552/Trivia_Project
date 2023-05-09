#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"

using std::string;
using std::vector;

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