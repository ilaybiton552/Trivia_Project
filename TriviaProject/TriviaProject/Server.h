#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"

#define EXIT "EXIT"

class Server
{
public:
	//Method
	void run();

private:
	//Field
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};

