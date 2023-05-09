#pragma once
#include "Structs.h"
class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};

