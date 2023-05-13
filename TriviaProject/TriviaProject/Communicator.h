#pragma once
#include <WinSock2.h>
#include <map>
#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#define RECV_OR_SEND 1024
#define REQUEST_ID_INDEX 0
#define HEADER_MESSAGE_SIZE 5

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
	RequestInfo receiveMessage(const SOCKET& clientSocket);
	void insertBackIntoVector(vector<unsigned char>& message, const unsigned char* buffer, const int numOfBytes);
	int initializeReceive(RequestInfo& requestInfo, const SOCKET& clientSocket);
	void sendMessageToClient(const vector<unsigned char>& message, const SOCKET& clientSocket);
	void printClientMessage(const vector<unsigned char>& message);

	//Fields
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
};

