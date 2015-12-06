// UDPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>


int main()
{
	int iResult = 0;
	WSADATA wsaData;
	DWORD ver = MAKEWORD(2, 2);

	SOCKET recvSock;
	SOCKADDR_IN recvAddr;
	SOCKADDR_IN senderAddr;

	unsigned short Port = 27015;

	char RecvBuf[1024];
	int BufLen = 1024;

	// Init winsock
	iResult = WSAStartup(ver, &wsaData);
	if (iResult != NO_ERROR) 
	{
		return 1;
	}

	// Create Receiver Socket
	recvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (recvSock == INVALID_SOCKET) 
	{
		return 1;
	}

	// Bind the socket
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	recvAddr.sin_port = htons(Port);

	iResult = bind(recvSock, (SOCKADDR*)&recvAddr, sizeof(recvAddr) );
	if (iResult != 0) 
	{
		return 1;
	}

	int senderAddrsize = sizeof(senderAddr);
	iResult = recvfrom(recvSock, RecvBuf, BufLen, 0, (SOCKADDR*)&senderAddr, &senderAddrsize);

	if (iResult == SOCKET_ERROR) 
	{
		return 1;
	}

	iResult = closesocket(recvSock);
	WSACleanup();

    return 0;
}

