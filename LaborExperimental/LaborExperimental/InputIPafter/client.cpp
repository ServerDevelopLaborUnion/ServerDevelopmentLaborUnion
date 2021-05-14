#include <WS2tcpip.h>
#include <cstdio>
#pragma comment(lib, "ws2_32")


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sClient;
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	printf("IPv4 (dotted decimal notation) �ּҸ� �Է��ϼ���.\r\n����: 192.168.0.1\r\n");


#pragma region �ּ� �� ���缭 ������

	// �̰ź��� �� ���� ����� ���� ��.
	wchar_t addr[16];
	scanf_s("%ws", addr, 16);

	INT addrSize = 0; // index ��ȣ�� + 1 ����� ��
	for (int i = 0; i < 16; ++i)
	{
		if (addr[i] == '\0')
		{
			addrSize = i + 1; 
		}
	}

	wchar_t* address = (wchar_t*)malloc(sizeof(wchar_t) * addrSize);
	for (int i = 0; i < addrSize; ++i)
	{
		address[i] = addr[i];
	}

#pragma endregion

	SOCKADDR_IN connectionData;
	InetPton(AF_INET, address, &connectionData.sin_addr);
	connectionData.sin_port = htons(56789);
	connectionData.sin_family = AF_INET;

	connect(sClient, (SOCKADDR*)&connectionData, sizeof(connectionData));
	printf("�����. IP: %ws\r\n", address);

	CHAR buffer[1024];
	INT bufferSize = 1024;
	INT leftBufferSize = bufferSize;
	INT lBuffer = 0;
	INT index = 0;

	// �ѹ��� buffer ���� �� �����ٰ� ��
	while (leftBufferSize > 0)
	{
		lBuffer = recv(sClient, &buffer[index], leftBufferSize, 0);
		printf("%s\r\n", &buffer[index]);
		leftBufferSize -= lBuffer;
		index += lBuffer;
	}
	
	//shutdown(sClient, SD_BOTH);

	closesocket(sClient);
	WSACleanup();
	free(address);

	system("pause");

	return(0);
}