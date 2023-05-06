#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	try
	{
		cout << "Starting..." << endl;
		WSAInitializer wsa_init;
		Server md_server;
		md_server.run();
	}
	catch (const std::exception& e)
	{
		cout << "Exception was thrown in function: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown exception in main !" << endl;
	}
}
