#pragma once
#include <WinSock2.h>
#include <map>
#include <iostream>
#include "IRequestHandler.h"

using std::map;
using std::cout;
using std::endl;

class Communicator
{
public:
	//Method
	void startHandleRequests();
private:
	//Methods
	void bindAndListen();
	void handleNewClient(const SOCKET client_socket);

	//Fields
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
};

