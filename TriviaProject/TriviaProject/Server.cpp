#include "Server.h"
#include <string>
#include "SqliteDatabase.h"

using std::string;
using std::cin;
using std::getline;

/// <summary>
/// Constructor of Server
/// </summary>
Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(m_database), m_communicator(m_handlerFactory)
{
	m_database->open();
}

/// <summary>
/// Destructor of Server
/// </summary>
Server::~Server()
{
	if (m_database != nullptr)
	{
		m_database->close();
		delete m_database;
	}
}

/// <summary>
/// Runs the server
/// </summary>
void Server::run()
{
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
}
