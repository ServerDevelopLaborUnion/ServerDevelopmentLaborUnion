#include <Windows.h>
#include <iostream>
#include <conio.h>

#define �߾� main

DWORD WINAPI �ͻ���(LPVOID lpParam);

int ���Ƿ罺 = 0;
CRITICAL_SECTION crit;

int �߾�()
{
	
	InitializeCriticalSection(&crit);

	HANDLE hThread;

	hThread = CreateThread(NULL, 0, �ͻ���, 0, 0, NULL);
	
	for (int ���� = 1; ���� <= 10000000; ++����)
	{
		EnterCriticalSection(&crit);
		���Ƿ罺 -= 1;
		LeaveCriticalSection(&crit);
	}


	WaitForSingleObject(hThread, INFINITE);
	
	std::cout << ���Ƿ罺 << std::endl;


	DeleteCriticalSection(&crit);
	return 0;
}

DWORD WINAPI �ͻ���(LPVOID lpParam)
{

	for (int ���� = 1; ���� <= 10000000; ++����)
	{
		EnterCriticalSection(&crit);
		���Ƿ罺 += 1;
		LeaveCriticalSection(&crit);
	}

	return 0;
}