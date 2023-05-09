#pragma once
#include <vector>
#include "Structs.h"
#include "json.hpp"

using json = nlohmann::json;
using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse errorResponse);
	static vector<unsigned char> serializeResponse(LoginResponse loginResponse);
	static vector<unsigned char> serializeResponse(SignupResponse signupResponse);
};

