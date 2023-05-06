#pragma once
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"

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
	std::map<SOCKET, IRequestHandler*> m_clients;
};

