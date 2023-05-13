#pragma once
#include "Structs.h"

struct RequestInfo; // problem of circular reference
struct RequestResult; // problem of circular reference

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};

