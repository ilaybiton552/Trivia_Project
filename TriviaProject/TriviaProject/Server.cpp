#include "Server.h"
#include <string>
#include "SqliteDatabase.h"

using std::string;
using std::cin;
using std::getline;

/// <summary>
/// Runs the server
/// </summary>
void Server::run()
{
	m_database = new SqliteDatabase();
	m_database->open();
	// creating a thread which gets new clients
	thread t_connector(&Communicator::startHandleRequests, std::ref(m_communicator));
	t_connector.detach();

	// getting commands from user
	string command;
	while (command != EXIT)
	{
		cout << "Enter the command: ";
		getline(cin, command);
	}
	m_database->close();
}
