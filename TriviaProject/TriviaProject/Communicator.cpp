#include "Communicator.h"

static const unsigned short PORT = 8826; // the server socket port that listen
static const unsigned int IFACE = 0;

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
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	cout<< "binded" << endl;

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	cout << "listening..." << endl;
}