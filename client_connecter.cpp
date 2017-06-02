#include "client_connecter.h"

ClientConnecter::~ClientConnecter()
{
	closesocket(m_contactSocket);
}

void ClientConnecter::Initialize(short portNumber, int backLog)
{
	if (m_isInitialized)
	{
		return;
	}

	m_contactSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (m_contactSocket == INVALID_SOCKET)
	{
		throw TCP_Exception("Socket creation failed..");
	}
	m_sockAddr.sin_port = htons(portNumber);
	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(m_contactSocket, (SOCKADDR*)&m_sockAddr, sizeof(m_sockAddr)) == SOCKET_ERROR)
	{
		throw TCP_Exception("Socket binding failed..");
	}

	listen(m_contactSocket, backLog);
	m_isInitialized = true;
}

bool ClientConnecter::Accept() noexcept
{
	if (!m_isInitialized)
	{
		return false;
	}

	int sockAddrSize = sizeof(m_sockAddr);
	SOCKADDR_IN clientAddr;
	SOCKET tempSocket = SOCKET_ERROR;
	while (tempSocket == SOCKET_ERROR)
	{
		tempSocket = accept(m_contactSocket, (SOCKADDR*)&clientAddr, &sockAddrSize);
	}
	m_threads.push_back(std::thread(SocketFunction, tempSocket));
	return true;
}