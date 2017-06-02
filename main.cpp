#include "client_connecter.h"
#include <iostream>

#define PORT_NUMBER 20000

int main()
{
	WSAInitializer wsaInit;
	try
	{
		wsaInit.Initialize();
	}
	catch (TCP_Exception tcpExc)
	{
		std::cout << tcpExc.what() << std::endl;
		return -1;
	}

	ClientConnecter server;
	try
	{
		server.Initialize(PORT_NUMBER);
	}
	catch (TCP_Exception tcpExc)
	{
		std::cout << tcpExc.what() << std::endl;
		return -1;
	}

	while (true)
	{
		if (server.Accept())
			std::cout << "Accepted..\n";
		else
			std::cout << "Not accepted..\n";
		std::cout << "Connected clients: " << server.Size() << std::endl;
	}
}