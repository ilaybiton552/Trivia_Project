#pragma once
#include "Communicator.h"

#define EXIT "EXIT"

class Server
{
public:
	//Method
	void run();

private:
	//Field
	Communicator m_communicator;
};

