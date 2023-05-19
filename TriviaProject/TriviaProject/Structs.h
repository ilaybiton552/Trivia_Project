#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"
#include "RoomData.h"

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

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomResponse
{
	unsigned int status;
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> players;
};

struct getHighScoreResponse
{
	unsigned int status;
	vector<string> statistics;
};

struct getPersonalStatsResponse
{
	unsigned int status;
	vector<string> statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
