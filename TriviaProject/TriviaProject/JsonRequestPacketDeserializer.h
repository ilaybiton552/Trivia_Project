#pragma once
#include <vector>
#include "Structs.h"

using std::vector;

class JsonRequestPacketDeserializer
{
public:
	LoginRequest deserializeLoginRequst(vector<unsigned char> buffer);
	LoginRequest deserializeSignupRequst(vector<unsigned char> buffer);
};

