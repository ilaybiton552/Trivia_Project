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
	unsigned int status;
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	unsigned int status;
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
	unsigned int roomId;
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

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	map<unsigned int, string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};

struct GetGameResultsResponse
{
	unsigned int status;
	vector<PlayerResults> results;
};

struct SubmitAnswerRequest
{
	unsigned int answerId;
};

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};