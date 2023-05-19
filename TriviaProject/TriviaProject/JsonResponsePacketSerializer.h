#pragma once
#include <vector>
#include "Structs.h"
#include "json.hpp"

#define MAX_BYTES_UNSIGNED_INT 4
#define NUM_OF_BITS_IN_BYTE 8
#define MAX_VALUE_OF_BYTE 255
#define ERROR_RESPONSE_CODE 200
#define LOGIN_RESPONSE_CODE 201
#define SIGNUP_RESPONSE_CODE 202
#define FIRST_BYTE_INDEX 3

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
private:
	static vector<unsigned char> convertNumberToByte(const unsigned int num);
	static vector<unsigned char> convertJsonToByte(const json jsonObject);
	static vector<unsigned char> makeSerializedPacket(const json packetData);
};

