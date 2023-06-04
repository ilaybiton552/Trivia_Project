#pragma once
#include <WinSock2.h>
#include <map>
#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"

#define RECV_OR_SEND 1024
#define REQUEST_ID_INDEX 0
#define HEADER_MESSAGE_SIZE 5
#define CLIENT_LOG_OUT 0

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
	Communicator(RequestHandlerFactory& handlerFactory); // c'tor
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
	void disconnectClient(const SOCKET& clientSocket);
	void handleClientsInRooms(const RequestInfo& requestInfo, const SOCKET& clientSocket);
	void sendToAllClientsPlayersInRoom(const vector<SOCKET>& clients, const Room& room);

	//Fields
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	map<unsigned int, vector<SOCKET>> m_roomsSocket; // <roomId, vector of sockets of clients in room>
};

