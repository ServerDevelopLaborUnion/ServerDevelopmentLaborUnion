#pragma once
#include <WS2tcpip.h>
#include "CRAIICriticalSession.h"
#include <stdio.h>
#include <queue>

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

#pragma region Thread
	HANDLE*			hRecvThread;
	HANDLE			hSendThread;
#pragma endregion

#pragma region Data
	std::queue<CHAR[PACKET_SIZE]> m_msgQueue;
#pragma endregion

public:
	CONSTRUCTOR CEasyServer();
	DESTRUCTOR	~CEasyServer();

	/// <summary>
	/// while(true) �� ������ ������ ���� �� ���� �����带 ����ϴ�.
	/// </summary>
	/// <returns>������ ���� �� -1, �������� �� 0</returns>
	INT _Must_inspect_result_ _Check_return_ acceptClient();
	INT _Must_inspect_result_ _Check_return_ waitSenderThread(); //��� ����

#pragma region Threads

#pragma region static
	inline static DWORD WINAPI senderThreadStart(LPVOID lpParam)
	{
		CEasyServer* This = (CEasyServer*)lpParam;
		return This->msgSenderThread();
	}
	inline static DWORD WINAPI recvThreadStart(LPVOID lpParam)
	{
		CEasyServer* This = (CEasyServer*)lpParam;
		return This->recvThread(sClient + clientNumber - 1);
	}
#pragma endregion

	


	DWORD msgSenderThread();
	DWORD recvThread(LPVOID lpParam);
#pragma endregion 
};