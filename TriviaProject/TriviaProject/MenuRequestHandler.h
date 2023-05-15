#pragma once
#include "IRequestHandler.h"
class MenuRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
