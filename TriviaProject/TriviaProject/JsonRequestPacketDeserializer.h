#pragma once
#include <vector>
#include "Structs.h"

#define NUM_OF_BITS_IN_BYTE 8

using std::vector;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequst(vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequst(vector<unsigned char> buffer);

private:
	static int convertByteToNumber(vector<unsigned char> buffer, int numOfBytes);
};

