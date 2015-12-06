// UDPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>


int main()
{
	int iResult = 0;

	WSADATA wsaData;
	SOCKADDR_IN sockAddr;

	SOCKET sendSok;

	unsigned int Port = 27015;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR ) 
	{
		return 1;
	}

	sendSok = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sendSok == INVALID_SOCKET) 
	{
		return 1;
	}

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(Port);
	inet_pton(AF_INET, "127.0.0.1", &(sockAddr.sin_addr));

	char message[1024] = "Hello There";

	if (sendto(sendSok, message, 1024, 0, (SOCKADDR*) &sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	WSACleanup();

    return 0;
}

