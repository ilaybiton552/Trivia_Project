#pragma once
#include "Communicator.h"

class Server
{
public:
	//Method
	void run();

private:
	//Field
	Communicator m_communicator;
};

