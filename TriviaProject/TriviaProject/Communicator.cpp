#include "Communicator.h"

static const unsigned short PORT = 8826; // the server socket port that listen
static const unsigned int IFACE = 0;
#define HELLO_MSG_LEN 5

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

		const char* helloMsg = "Hello";
		cout << "Sending Hello message to client..." << endl;
		if (send(client_socket, helloMsg, HELLO_MSG_LEN, 0) == INVALID_SOCKET) // send the hello message to the client
		{
			throw exception("Error while sending message to client");
		}

		char* data = new char[HELLO_MSG_LEN + 1];
		int res = recv(client_socket, data, HELLO_MSG_LEN, 0); // get the client answer
		if (res == INVALID_SOCKET)
		{
			string err = "Error while recieving from socket: ";
			err += std::to_string(client_socket);
			throw exception(err.c_str());
		}
		data[HELLO_MSG_LEN] = 0;
		string received(data);
		delete[] data;

		if (received != "Hello")
		{
			throw exception("The client didn't answer properly");
		}
		cout << "Client answer: " << received << endl;
	}
	catch (const exception& e)
	{
		cout << "Exception was catch in function handleNewClient. Socket = " << client_socket << ", what = " << e.what() << endl;
	}
}