#pragma once
#include <vector>
#include "Structs.h"
#include "json.hpp"

#define MAX_BYTES_UNSIGNED_INT 4
#define NUM_OF_BITS_IN_BYTE 8
#define MAX_VALUE_OF_BYTE 255
#define FIRST_BYTE_INDEX 3

enum RESPONSE_CODES {ERROR_RESPONSE_CODE = 200, LOGIN_RESPONSE_CODE, SIGNUP_RESPONSE_CODE, LOGOUT_RESPONSE_CODE, GET_ROOM_RESPONSE_CODE, 
			GET_PLAYERS_IN_ROOM_RESPONSE_CODE, JOIN_ROOM_RESPONSE_CODE, CREATE_ROOM_RESPONSE_CODE, GET_HIGH_SCORE_RESPONSE_CODE, 
			GET_PERSONAL_STATS_RESPONSE_CODE, CLOSE_ROOM_RESPONSE_CODE, START_GAME_RESPONSE_CODE, GET_ROOM_STATE_RESPONSE_CODE,
			LEAVE_ROOM_RESPONSE_CODE, LEAVE_GAME_RESPONSE_CODE, GET_QUESTION_RESPONSE_CODE, SUBMIT_ANSWER_RESPONSE_CODE,
			GET_GAME_RESULTS_RESPONSE, ADD_QUESTION_RESPONSE_CODE};


using json = nlohmann::json;
using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse errorResponse);
	static vector<unsigned char> serializeResponse(LoginResponse loginResponse);
	static vector<unsigned char> serializeResponse(SignupResponse signupResponse);
	static vector<unsigned char> serializeResponse(LogoutResponse logoutResponse);
	static vector<unsigned char> serializeResponse(GetRoomResponse getRoomResponse);
	static vector<unsigned char> serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResponse);
	static vector<unsigned char> serializeResponse(JoinRoomResponse joinRoomResponse);
	static vector<unsigned char> serializeResponse(CreateRoomResponse createRoomResponse);
	static vector<unsigned char> serializeResponse(getHighScoreResponse scoreResponse);
	static vector<unsigned char> serializeResponse(getPersonalStatsResponse statsResponse);
	static vector<unsigned char> serializeResponse(CloseRoomResponse closeRoomResponse);
	static vector<unsigned char> serializeResponse(StartGameResponse startGameResponse);
	static vector<unsigned char> serializeResponse(GetRoomStateResponse getRoomStateResponse);
	static vector<unsigned char> serializeResponse(LeaveRoomResponse leaveRoomResponse);
	static vector<unsigned char> serializeResponse(GetGameResultsResponse getGameResultsResponse);
	static vector<unsigned char> serializeResponse(SubmitAnswerResponse submitAnswerResponse);
	static vector<unsigned char> serializeResponse(GetQuestionResponse getQuestionResponse);
	static vector<unsigned char> serializeResponse(LeaveGameResponse leaveGameResponse);
	static vector<unsigned char> serializeResponse(AddQuestionResponse addQuestionResponse);
private:
	static vector<unsigned char> convertNumberToByte(const unsigned int num);
	static vector<unsigned char> convertJsonToByte(const json jsonObject);
	static vector<unsigned char> makeSerializedPacket(const json packetData, const int code);
};

