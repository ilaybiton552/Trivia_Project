#include "Communicator.h"

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
		LoginRequestHandler* pLoginRequest = new LoginRequestHandler;
		m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, pLoginRequest)); // add the client to the client map

		vector<unsigned char> clientsMessage = receiveMessage(client_socket);
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
/// <returns>vector of bytes, the message of the client</returns>
vector<unsigned char> Communicator::receiveMessage(const SOCKET& clientSocket)
{
	unsigned char buffer[RECV];
	vector<unsigned char> message;
	bool receiving = true; // if still receiving from the client
	int numOfBytes = 0; // number of bytes received from client

	cout << "Client's message: ";
	while (receiving)
	{
		numOfBytes = recv(clientSocket, (char*)buffer, RECV, 0);
		cout << buffer;
		if (numOfBytes == SOCKET_ERROR)
		{
			throw exception("Error getting client's message from socket: " + clientSocket);
		}
		if (numOfBytes <= RECV)
		{
			receiving = false;
		}
		insertBackIntoVector(message, buffer, numOfBytes);
	}
	cout << endl;

	return message;
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
