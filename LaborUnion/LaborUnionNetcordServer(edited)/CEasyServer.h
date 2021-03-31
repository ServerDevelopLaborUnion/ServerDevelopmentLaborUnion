#pragma once
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

class CEasyServer
{
private:
#pragma region Client
	SOCKET*			sClient;
	SOCKADDR_IN*	clientAddr;
	INT				clientSize;
#pragma endregion

#pragma region Server
	SOCKADDR_IN		serverAddr;
	WSADATA			wsaData;
	INT				clientNumber;
#pragma endregion

	
public:
	CEasyServer();
	~CEasyServer();

	/// <summary>
	/// while(true) �� ������ ������ ���� �� ���� �����带 ����ϴ�.
	/// </summary>
	/// <returns></returns>
	INT acceptClient();

};

