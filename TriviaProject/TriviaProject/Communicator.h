#pragma once
#include <WinSock2.h>
#include <map>
#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#define RECV 1024

using std::map;
using std::pair;
using std::cout;
using std::endl;
using std::thread;
using std::exception;
using std::string;

class Communicator
{
public:
	Communicator(); // c'tor
	~Communicator(); // d'tor

	//Method
	void startHandleRequests();
private:
	//Methods
	void bindAndListen();
	void handleNewClient(const SOCKET client_socket);
	vector<unsigned char> receiveMessage(const SOCKET& clientSocket);
	void insertBackIntoVector(vector<unsigned char>& message, const unsigned char* buffer, const int numOfBytes);

	//Fields
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
};

