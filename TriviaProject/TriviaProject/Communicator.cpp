#include "Communicator.h"
#include "JsonResponsePacketSerializer.h"

static const unsigned short PORT = 8826; // the server socket port that listen
static const unsigned int IFACE = 0;

/// <summary>
/// Constructor of Communicater
/// </summary>
Communicator::Communicator()
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
			delete it->second; // deleting the allocated memory for the pointer
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

			LoginRequestHandler* pLoginRequest = new LoginRequestHandler;
			m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, pLoginRequest)); // add the client to the client map

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
		IRequestHandler* clientHandler = m_clients[client_socket];
		if (clientHandler->isRequestRelevant(requestInfo))
		{
			RequestResult requestResult = clientHandler->handleRequest(requestInfo);
			sendMessageToClient(requestResult.response, client_socket);
		}
		else
		{
			ErrorResponse errorResponse = { "ERROR" };
			sendMessageToClient(JsonResponsePacketSerializer::serializeResponse(errorResponse), client_socket);
		}
	}
	catch (const exception& e)
	{
		cout << "Exception was catch in function handleNewClient. Socket = " << client_socket << ", what = " << e.what() << endl;
	}
}

/// <summary>
/// Receiving messages
/// </summary>
/// <param name="clientSocket">SOCKET, the socket of the client to wait for receive</param>
/// <returns>Request, the info of the message of the client</returns>
RequestInfo Communicator::receiveMessage(const SOCKET& clientSocket)
{
	unsigned char buffer[RECV_OR_SEND];
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
	cout << endl;
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
	cout << "Client's message: " << endl << "Id: " << requestInfo.id << endl;

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
