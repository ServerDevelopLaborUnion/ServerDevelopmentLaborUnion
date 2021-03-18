#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
	// WSA == (WebSocketAPI, WinSockAPI, WebServiceAPI...)
	WSAData wsaData;
	
	// ���⼭ wsaData�� ������ �־� ���.
	// �Լ��� �˾Ƽ� ���ִ� ���� ����
	WSAStartup(MAKEWORD(2, 2), &wsaData); // ���߿� ��� Ŭ������ �����ڿ� ����ϴٰ� ���� �ſ�.
	
	// MAKEWORD == �Լ��� ���� ���� WORD(short) �����̶� �Ҽ����� ���� �� �����.
	//			   MAKEWORD(x, y) �� x.y �� ���� �������.
	//			   ���� �ڻ��� �����Ϸ��� ���

	SOCKET serverSocket; // ���� ����ü ����
	SOCKADDR_IN serverAddr; // ���� ���� ����ü ����
	{ // ������ ���ؼ� �߰�ȣ ����߾��.
		serverAddr.sin_family = AF_INET; // #define �� ����ؼ� ���ڸ� ���ڷ� �ٲ�� �ſ���. (���� ����ϱ� ����) (���콺 �÷� ���� �� �� ����)
		// AF_INET  �� 192.168.0.2			�� ���� ����.����.����.���� �� �� �ּҸ� �ǹ��ؿ�.
		// AF_INET6 �� 2001:0DB8::1428:57ab �� ���� ����� 16������ �� �ּҸ� �Ǹ��ؿ�.

		serverAddr.sin_port = htons(5678); // ��Ʈ ��ȣ�� ����� ������ short �ȿ��� ǥ���� ������ ���� �ؾ� �ؿ�. + http/s ��� ���� ���Ǵ� ��Ʈ�� ����� �� �����.
		// 12345678 �� �޸𸮿� �����ϴ� ���
		// ���ͳ� ǥ�� 12 34 56 78
		// ��ǻ�� ǥ�� 78 56 34 12
		// ���� ����� �޶� ���� ��ȯ�ؾ� �ؿ�.
		// htons == Host To Network Short (Host �� Network ��ġ�� �ٲٸ� Network ���� Host �� ��ȯ�� �����ؿ�)

		InetPton(AF_INET, TEXT("127.0.0.1"), &serverAddr.sin_addr);
		// TEXT("�ּ�") �� �� ������ char �� 1����Ʈ ������ ���ڸ� ����������,
		// InetPton �Լ��� 2����Ʈ ������ �����ϴ� wchar_t �� �䱸�ؼ� ��ȯ�� �ʿ��߾��.
		// ����.����.����.���� �� �̷���� ���ڿ��� ���ڷ� ��ȯ�Ͽ� serverAddr.sin_addr �� �־��ִ� �Լ�����.
	}
	
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// SOCK_STREAM = TCP/IP �� ����Ѵٴ� �ǹ̶�� �ϴ� �����ҰԿ�.
	// IPPROTO_TCP = TCP ��� ���������� ����Ѵٴ� �ǹ̿���.

	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // ���� ����ü ������ �츮�� �ۼ��� ���� ������ ���� �ִ� ������ �մϴ�.
	// (SOCKADDR*)&serverAddr == ���� �ð��� �����ҰԿ�.
	
	WSACleanup(); // ���߿� ��� Ŭ������ �Ҹ��ڿ� ����ϴٰ� ���� �˴ϴ�.
	return 0;
}