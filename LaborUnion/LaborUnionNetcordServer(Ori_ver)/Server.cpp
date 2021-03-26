#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#pragma comment(lib, "ws2_32")

#define ONE2N

#ifdef ONE2N // ������ ���� 1��N ��� ����

DWORD WINAPI ConnectionThread(LPVOID lpParam);
DWORD WINAPI RecvThread(LPVOID lpParam);

std::queue<LPSTR>* g_msgQueue;


SOCKET* sListening;
SOCKET* sClient;
SOCKADDR_IN* serverAddr;
SOCKADDR_IN* clientAddr;
INT* clientAddrSize;
bool* clientConnect;
UINT* clientNum;

int main()
{
	WSADATA	wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#pragma region ä�� �� ũ��
	UINT	roomSize = -1;
	printf("�� ��� ü���ұ��?: ");
	while (true)
	{
		roomSize = -1;
		scanf_s("%d", &roomSize);
		if (roomSize >= 10)
		{
			printf("�ƴ� �󸶳� �Է��Ѱſ���;;\r\n");
			continue;
		}
		break;
	}
	printf("%d ���� ������ �� �ִ� ü�� ������ ����ϴ�\r\n", roomSize);
#pragma endregion

	HANDLE* hThread = new HANDLE[roomSize];

	g_msgQueue = new std::queue<LPSTR>[roomSize];

	sListening = new SOCKET[roomSize];
	sClient = new SOCKET[roomSize];
	serverAddr = new SOCKADDR_IN[roomSize];
	clientAddr = new SOCKADDR_IN[roomSize];
	clientAddrSize = new INT[roomSize];

	clientConnect = new bool[roomSize] { false };
	clientNum = new UINT[roomSize];

	for (UINT i = 0; i < roomSize; ++i)
	{
		if (i == 0)
		{
			clientNum[i] = i;
			hThread[i] = CreateThread(NULL, 0, ConnectionThread, &clientNum[i], 0, NULL);
		}
		else
		{
			while (true)
			{
				if (clientConnect[i - 1])
				{
					clientNum[i] = i;
					hThread[i] = CreateThread(NULL, 0, ConnectionThread, &clientNum[i], 0, NULL);
					break;
				}
			}
		}
	}

	WaitForMultipleObjects(roomSize, hThread, true, INFINITE);
	delete[] hThread;

	WSACleanup();
	return(0);
}

// ������ ���� �ּ�
// while(true)�� ���ѷ��� �ɰ�
// �� �ȿ� socket, bind, listen, accept ���� �� ���� CreateThread
// �׸��� �ٽ� ó������ ���ư�
// while �� ó���� ���������ϸ� ��ǻ�Ͱ� ������ �ȿ��� �������� ���� ����

DWORD WINAPI ConnectionThread(LPVOID lpParam)
{

	CRITICAL_SECTION crit;
	InitializeCriticalSection(&crit);

	UINT index = *(UINT*)lpParam;
	clientAddrSize[index] = sizeof(clientAddr[index]);

	serverAddr[index]; // ���� ���ϰ� �ϱ� ����
	{
		serverAddr[index].sin_addr.s_addr = INADDR_ANY;
		serverAddr[index].sin_port = htons(5678);
		serverAddr[index].sin_family = AF_INET;
	}
	sListening[index] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListening[index], (SOCKADDR*)&serverAddr[index], sizeof(serverAddr[index]));
	listen(sListening[index], SOMAXCONN);
	sClient[index] = accept(sListening[index], (SOCKADDR*)&clientAddr[index], &clientAddrSize[index]); // ERROR: WSAEINVAL 10022
	if (sClient[index] == INVALID_SOCKET)
	{
		printf("%x", WSAGetLastError());
		return(0);
	}
	closesocket(sListening[index]);
	clientConnect[index] = true;

	CreateThread(NULL, 0, RecvThread, lpParam, 0, NULL);

	while (true)
	{
		EnterCriticalSection(&crit);
		if (g_msgQueue[index].size() != 0)
		{
			send(sClient[index], g_msgQueue[index].front(), 1024, 0);
			g_msgQueue[index].pop();
		}
		LeaveCriticalSection(&crit);
	}

	closesocket(sClient[index]);
	DeleteCriticalSection(&crit);
	return 0;
}

DWORD WINAPI RecvThread(LPVOID lpParam)
{
	UINT index = *(UINT*)lpParam;
	CHAR chMsg[1024];

	CRITICAL_SECTION crit;
	InitializeCriticalSection(&crit);
	while (recv(sClient[index], chMsg, 1024, 0) != -1)
	{
		printf("%s\r\n", chMsg);
		EnterCriticalSection(&crit);
		g_msgQueue[index].push(chMsg);
		LeaveCriticalSection(&crit);
	}
	DeleteCriticalSection(&crit);

	return 0;
}
#endif