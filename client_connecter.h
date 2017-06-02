#pragma once
#include "network.h"
#include "db_connecter.h"
#include <vector>
#include <string>
#include <mutex>
#include <thread>

DBConnecter connecter;
std::mutex mtx;

std::string GetSQLCode(const std::string& request)
{
	std::string sqlCode{ "select " };
	//////////////////////////////////////
	return sqlCode;
}

void SocketFunction(SOCKET& i_socket)
{
	while (true)
	{
		char buffer[512];
		int retVal = recv(i_socket, buffer, 512, NULL);
		if (retVal <= 0 || retVal > 512)
			break;

		std::string sqlCode = GetSQLCode(std::string(buffer));
		mtx.lock();
		std::string answer = connecter.SQLRequest(sqlCode);
		mtx.unlock();
		retVal = send(i_socket, (char*)answer.c_str(), answer.size() + 1, NULL);
		if (retVal <= 0 || retVal > answer.size())
			break;
	}
	closesocket(i_socket);
}

class ClientConnecter
{
public:
	~ClientConnecter();
	void Initialize(short, int = 1);
	bool Accept() noexcept;
	size_t Size() const noexcept { return m_threads.size(); }

private:
	SOCKET                    m_contactSocket;
	std::vector<std::thread>  m_threads;
	SOCKADDR_IN               m_sockAddr;
	bool                      m_isInitialized = false;
};
