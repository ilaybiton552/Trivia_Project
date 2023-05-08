#include "Server.h"
#include <string>

using std::string;
using std::cin;
using std::getline;

/// <summary>
/// Runs the server
/// </summary>
void Server::run()
{
	// creating a thread which gets new clients
	thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();

	// getting commands from user
	string command;
	while (command != EXIT)
	{
		cout << "Enter the command: ";
		getline(cin, command);
	}
}
