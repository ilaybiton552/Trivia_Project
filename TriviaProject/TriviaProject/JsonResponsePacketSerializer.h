#pragma once
#include <vector>

using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse errorResponse);
	static vector<unsigned char> serializeResponse(LoginResnose loginResponse);
	static vector<unsigned char> serializeResponse(SignupResponse signupResponse);
};

