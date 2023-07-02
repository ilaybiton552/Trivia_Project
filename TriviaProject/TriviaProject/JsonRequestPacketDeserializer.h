#pragma once
#include <vector>
#include "Structs.h"
#include "json.hpp"

#define NUM_OF_BITS_IN_BYTE 8
#define MAX_BYTES_UNSIGNED_INT 4
#define START_OF_NUM_OF_BYTES 1
#define START_OF_DATA 5

using std::vector;
using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const vector<unsigned char>& buffer);
	static SignupRequest deserializeSignupRequest(const vector<unsigned char>& buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const vector<unsigned char>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const vector<unsigned char>& buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const vector<unsigned char>& buffer);
	static AddQuestionRequest deserializeAddQuestionRequest(const vector<unsigned char>& buffer);
private:
	static json getJsonFromBuffer(const vector<unsigned char>& buffer);
};

