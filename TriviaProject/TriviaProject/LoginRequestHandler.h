#pragma once
#include "IRequestHandler.h"
#include "Structs.h"

#define NUM_OF_BITS_IN_BYTE 8
#define MAX_BYTES_UNSIGNED_INT 4
#define LOGIN_REQUEST 101
#define SIGNUP_REQUEST 102
#define SUCCESS_LOGIN_SIGNUP 1

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	static unsigned int convertByteToNumber(const vector<unsigned char>& buffer);
};

