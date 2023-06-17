#include "Communicator.h"
#include "JsonResponsePacketSerializer.h"

static const unsigned short PORT = 8826; // the server socket port that listen
static const unsigned int IFACE = 0;

/// <summary>
/// Constructor of Communicater
/// </summary>
/// <param name="handlerFactory">reference of RequestHandlerFactory, the handler factory of the server</param>
Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
	// opening the server socket
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

/// <summary>
/// Destructor of Communicator
/// </summary>
Communicator::~Communicator()
{
	try
	{
		closesocket(m_serverSocket);
		for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
		{
			closesocket(it->first); // closing the clients socket
			if (it->second != nullptr)
			{
				delete it->second; // deleting the allocated memory for the pointer
				it->second = nullptr;
			}
		}
	}
	catch(...) {}
}

/// <summary>
/// the function start to handle new clients, accepts clients and create a thread for every new client
/// </summary>
void Communicator::startHandleRequests()
{
	try
	{
		bindAndListen(); // want to bind and then start listening
		while (true)
		{
			SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
			if (client_socket == INVALID_SOCKET)
			{
				throw exception(__FUNCTION__);
			}

			cout << "Client accepted !" << endl;

			m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, m_handlerFactory.createLoginRequestHandler())); // add the client to the client map

			// create new thread for client	and detach from it
			thread client_thread(&Communicator::handleNewClient, this, client_socket);
			client_thread.detach();
		}
	}
	catch (const  exception& e)
	{
		cout << e.what() << endl;
	}
}

/// <summary>
/// the function creates a socket that listen to connecting requests from clients
/// </summary>
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;

	// again stepping out to the global namespace
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw exception(__FUNCTION__ " - bind");
	}
	cout << "binded" << endl;

	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw exception(__FUNCTION__ " - listen");
	}
	cout << "listening..." << endl;
}

/// <summary>
/// the function handles the new client
/// </summary>
/// <param name="client_socket">the client socket to handle</param>
void Communicator::handleNewClient(const SOCKET client_socket)
{
	try
	{
		RequestInfo requestInfo = receiveMessage(client_socket);
		while (requestInfo.id != CLIENT_LOG_OUT)
		{
			IRequestHandler* clientHandler = m_clients[client_socket];
			int roomId = 0; // in case of leave/close room, want to get the id before handling the request (changes the handler)
			if (clientHandler->isRequestRelevant(requestInfo))
			{
				if (requestInfo.id == LEAVE_ROOM_CODE || requestInfo.id == CLOSE_ROOM_CODE || requestInfo.id == START_GAME_CODE)
				{
					roomId = getRoomId(requestInfo.id, clientHandler);
				}
				RequestResult requestResult = clientHandler->handleRequest(requestInfo);
				sendMessageToClient(requestResult.response, client_socket);
				if (requestResult.newHandler != nullptr)
				{
					delete m_clients[client_socket];
					m_clients[client_socket] = requestResult.newHandler;
					if (requestInfo.id != GET_ROOM_STATE_CODE && requestInfo.id >= JOIN_ROOM_CODE && requestInfo.id <= LEAVE_ROOM_CODE)
					{
						handleClientsInRooms(requestInfo.id, client_socket, requestResult.newHandler, roomId);
					}
				}
			}
			else
			{
				ErrorResponse errorResponse = { "ERROR" };
				sendMessageToClient(JsonResponsePacketSerializer::serializeResponse(errorResponse), client_socket);
			}
			requestInfo = receiveMessage(client_socket);
		}
		disconnectClient(client_socket);
	}
	catch (const exception& e)
	{
		cout << "Exception was catch in function handleNewClient. Socket = " << client_socket << ", what = " << e.what() << endl;
		disconnectClient(client_socket);
	}
}

/// <summary>
/// Receiving messages
/// </summary>
/// <param name="clientSocket">SOCKET, the socket of the client to wait for receive</param>
/// <returns>Request, the info of the message of the client</returns>
RequestInfo Communicator::receiveMessage(const SOCKET& clientSocket)
{
	unsigned char buffer[RECV_OR_SEND] = { 0 };
	vector<unsigned char> message;
	RequestInfo requestInfo;
	int recvResult = 0; // number of bytes received from client
	int messageNumOfBytes = 0; // number of bytes on the data message

	messageNumOfBytes = initializeReceive(requestInfo, clientSocket);
	cout << "Num of bytes: " << messageNumOfBytes << endl;

	while (messageNumOfBytes != 0)
	{
		recvResult = recv(clientSocket, (char*)buffer, RECV_OR_SEND, 0);
		if (recvResult == SOCKET_ERROR)
		{
			throw exception("Error getting client's message from socket: " + clientSocket);
		}
		messageNumOfBytes -= recvResult;
		insertBackIntoVector(message, buffer, recvResult);
	}

	cout << "Data: ";
	printClientMessage(message);
	cout << endl << endl;
	requestInfo.buffer = message;

	return requestInfo;
}

/// <summary>
/// Inserts into the vector of the message the buffer info
/// </summary>
/// <param name="message">vector of bytes, the message of the client</param>
/// <param name="buffer">array of bytes, the buffer from the socket</param>
/// <param name="numOfBytes">int, the number of bytes to read from the socket</param>
void Communicator::insertBackIntoVector(vector<unsigned char>& message, const unsigned char* buffer, const int numOfBytes)
{
	for (int i = 0; i < numOfBytes; i++)
	{
		message.push_back(buffer[i]);
	}
}

/// <summary>
/// Performs the initialize receive
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <param name="clientSocket">SOCKET, the socket of the client to wait for receive</param>
/// <returns>int, the number of bytes the data has</returns>
int Communicator::initializeReceive(RequestInfo& requestInfo, const SOCKET& clientSocket)
{
	unsigned char buffer[RECV_OR_SEND] = { 0 };

	// receives message code and num of data size
	int recvResult = recv(clientSocket, (char*)buffer, HEADER_MESSAGE_SIZE, 0);
	if (recvResult == SOCKET_ERROR)
	{
		throw exception("Error getting client's message from socket: " + clientSocket);
	}
	requestInfo.receivalTime = time(0);
	requestInfo.id = LoginRequestHandler::convertByteToNumber(vector<unsigned char>(1, buffer[REQUEST_ID_INDEX]));
	cout << endl << "Client's message: " << endl << "Id: " << requestInfo.id << endl;

	vector<unsigned char> dataBytes;
	insertBackIntoVector(dataBytes, buffer, HEADER_MESSAGE_SIZE);
	dataBytes.erase(dataBytes.begin());
	return LoginRequestHandler::convertByteToNumber(dataBytes);
}

/// <summary>
/// Sends a response for the client
/// </summary>
/// <param name="buffer">vector of bytes, the message to send</param>
/// <param name="clientSocket">SOCKET, the socket of the client</param>
void Communicator::sendMessageToClient(const vector<unsigned char>& message, const SOCKET& clientSocket)
{
	int numOfBytesToSend = 0;
	vector<unsigned char> dataSize;

	// num of bytes to send
	for (int i = 1; i < HEADER_MESSAGE_SIZE; i++)
	{
		dataSize.push_back(message[i]);
	}
	numOfBytesToSend = LoginRequestHandler::convertByteToNumber(dataSize) + HEADER_MESSAGE_SIZE;
	
	// convert vector to array
	unsigned char* buffer = new unsigned char[numOfBytesToSend];
	for (int i = 0; i < numOfBytesToSend; i++)
	{
		buffer[i] = message[i];
	}

	int sendResult = send(clientSocket, (char*)buffer, numOfBytesToSend, 0);
	if (sendResult == SOCKET_ERROR)
	{
		throw exception("Error sending message to client,  socket: " + clientSocket);
	}
	delete[] buffer;
}

/// <summary>
/// prints the client message
/// </summary>
/// <param name="message">vector of bytes, the message of the client</param>
void Communicator::printClientMessage(const vector<unsigned char>& message)
{
	for (auto it = message.begin(); it != message.end(); ++it)
	{
		cout << *it;
	}
}

/// <summary>
/// Disconnects a cilent from the server
/// </summary>
/// <param name="clientSocket">SOCKET, the socket of the client</param>
void Communicator::disconnectClient(const SOCKET& clientSocket)
{
	IRequestHandler* requestHandler = m_clients[clientSocket];
	if (requestHandler != nullptr)
	{
		// loging out the user from logged users if this is MenuRequestHandler
		RequestInfo info = { SIGNOUT_CODE };
		if (requestHandler->isRequestRelevant(info))
		{
			requestHandler->handleRequest(info);
		}
		delete requestHandler;
		requestHandler = nullptr;
	}
	m_clients.erase(clientSocket);
	closesocket(clientSocket);
}

/// <summary>
/// Handles clients in rooms and updates them according to the request information
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <param name="clientSocket">SOCKET, the socket of the current client</param>
/// <param name="roomId">unsigned int, the id of the room</param>
void Communicator::handleClientsInRooms(const unsigned int code, const SOCKET& clientSocket, IRequestHandler* clientHandler, unsigned int roomId)
{
	if (code == CREATE_ROOM_CODE)
	{
		roomId = static_cast<RoomAdminRequestHandler*>(clientHandler)->getRoomId();
		m_roomsSocket[roomId].push_back(clientSocket);
	}
	else if (code == JOIN_ROOM_CODE)
	{
		Room room = static_cast<RoomMemberRequestHandler*>(clientHandler)->getRoom();
		roomId = room.getRoomData().id;
		sendToAllClientsPlayersInRoom(m_roomsSocket[roomId], room);
		m_roomsSocket[roomId].push_back(clientSocket);
	}
	else if (code == START_GAME_CODE)
	{
		StartGameResponse response = { STATUS_SUCCESS };
		Game game = static_cast<GameRequestHandler*>(clientHandler)->getGame();
		sendMessageToAllClients(m_roomsSocket[roomId], JsonResponsePacketSerializer::serializeResponse(response), clientSocket, true, &game);
		// deleting the room (after the game sends to menu)
		m_handlerFactory.getRoomManager().deleteRoom(roomId); 
		m_roomsSocket.erase(roomId);
	}
	else if (code == LEAVE_ROOM_CODE)
	{
		// erasing the client's socket from the room
		for (auto it = m_roomsSocket[roomId].begin(); it != m_roomsSocket[roomId].end(); ++it)
		{
			if (*it == clientSocket)
			{
				m_roomsSocket[roomId].erase(it);
				break;
			}
		}
		sendToAllClientsPlayersInRoom(m_roomsSocket[roomId], m_handlerFactory.getRoomManager().getRoom(roomId));
	}
	else // close room
	{
		LeaveRoomResponse response = { STATUS_CLOSED_ROOM };
		sendMessageToAllClients(m_roomsSocket[roomId], JsonResponsePacketSerializer::serializeResponse(response), clientSocket, true);
		m_roomsSocket.erase(roomId);
	}
}

/// <summary>
/// Sends to all of the clients in a room list of the players in the room
/// </summary>
/// <param name="clients">vector of SOCKET, the clients in the room</param>
/// <param name="room">Room, the room</param>
void Communicator::sendToAllClientsPlayersInRoom(const vector<SOCKET>& clients, const Room& room)
{
	// getting list of all of the players in the room
	GetPlayersInRoomResponse response = { STATUS_SUCCESS, room.getAllUsers() };
	vector<unsigned char> message = JsonResponsePacketSerializer::serializeResponse(response);

	sendMessageToAllClients(clients, message);
}

/// <summary>
/// Sends message to all of the clients
/// </summary>
/// <param name="clients">vector of SOCKET, the clients to send the message to</param>
/// <param name="message">vector of bytes, the message to send</param>
/// <param name="clientSocket">SOCKET, the socket of the client, if don't want to send a message back to him</param>
/// <param name="changeHandler">bool, if need to change the handler</param>
/// <param name="game">pointer of game, if null - menu handler, if not - game handler</param>
void Communicator::sendMessageToAllClients(const vector<SOCKET>& clients, const vector<unsigned char>& message, const SOCKET& clientSocket, const bool changeHandler, Game* pGame)
{
	// sends to every client the list of players
	for (auto it = clients.begin(); it != clients.end(); ++it)
	{
		if (*it != clientSocket)
		{
			sendMessageToClient(message, *it);
			if (changeHandler) // will be true for start game or close room
			{
				IRequestHandler** pCurrHandler = &m_clients[*it];

				// will always be room member request handler
				LoggedUser loggedUser = static_cast<RoomMemberRequestHandler*>(*pCurrHandler)->getLoggedUser();
				delete *pCurrHandler;

				if (pGame == nullptr) // close room case
				{
					*pCurrHandler = m_handlerFactory.createMenuRequestHandler(loggedUser);
				}
				else // game handler (start game case)
				{
					*pCurrHandler = m_handlerFactory.createGameRequestHandler(loggedUser, *pGame);
				}
			}
		}
	}
}

/// <summary>
/// Gets the id of the room according to the handler of the client and the request
/// </summary>
/// <param name="code">unsigned int, the code of the request</param>
/// <param name="clientHanlder">IRequestHandler, the handler of the client</param>
/// <returns>unsigned int, the id of the room</returns>
unsigned int Communicator::getRoomId(const unsigned int code, IRequestHandler* clientHanlder)
{
	if (code == LEAVE_ROOM_CODE)
	{
		return static_cast<RoomMemberRequestHandler*>(clientHanlder)->getRoom().getRoomData().id;
	}
	return static_cast<RoomAdminRequestHandler*>(clientHanlder)->getRoomId();
}
