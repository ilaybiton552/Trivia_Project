#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>

using std::cout;
using std::endl;
using std::exception;

int main()
{
	try
	{
		cout << "Starting..." << endl;
		WSAInitializer wsa_init;
		Server md_server;
		md_server.run();
	}
	catch (const exception& e)
	{
		cout << "Exception was thrown in function: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown exception in main !" << endl;
	}
}
