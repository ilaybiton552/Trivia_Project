#pragma once
#include "IRequestHandler.h"
#include "Structs.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;
};

