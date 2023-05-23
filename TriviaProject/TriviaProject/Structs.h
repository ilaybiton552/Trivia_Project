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

struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomResponse
{
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> players;
};

struct getHighScoreResponse
{
	vector<std::pair<string, unsigned int>> statistics;
};

struct getPersonalStatsResponse
{
	unsigned int numOfGames;
	unsigned int rightAnswers;
	unsigned int wrongAnswers;
	float averageTime;
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
