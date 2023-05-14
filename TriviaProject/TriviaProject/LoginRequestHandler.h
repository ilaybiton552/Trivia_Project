#pragma once
#include "IRequestHandler.h"
#include "Structs.h"
#include "RequestHandlerFactory.h"

#define NUM_OF_BITS_IN_BYTE 8
#define LOGIN_REQUEST 101
#define SIGNUP_REQUEST 102
#define SUCCESS_LOGIN_SIGNUP 1

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
	static unsigned int convertByteToNumber(const vector<unsigned char>& buffer);
private:
	RequestHandlerFactory& m_handlerFactory;

};

