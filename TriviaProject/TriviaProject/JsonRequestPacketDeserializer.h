#pragma once
#include <vector>
#include "Structs.h"

#define NUM_OF_BITS_IN_BYTE 8
#define MAX_BYTES_UNSIGNED_INT 4

using std::vector;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequst(vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequst(vector<unsigned char> buffer);

private:
	static unsigned int convertByteToNumber(vector<unsigned char> buffer);
};

