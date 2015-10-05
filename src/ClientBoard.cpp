#include "ClientBoard.h"

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

const int BUFLEN = 1024;
const int MAX_IP_SIZE = 15;

using namespace std;

ClientBoard::ClientBoard() :
		IBoard() {
}

void ClientBoard::Client() {

	struct sockaddr_in ClientAddr;
	int Connect;
	int addrLen;
	char buffer[BUFLEN];
	char message[BUFLEN];
	const char connected[BUFLEN] = "Message from client: Client connected.";
	char ip[MAX_IP_SIZE];
	short port;

	addrLen = sizeof(ClientAddr);

	cout << "Client:" << endl;

	cout << "Enter IP: ";
	cin >> ip;
	LOG(INFO, "ServerBoard::Client() " << "IP: " << ip);
	cout << "Enter Port: ";
	cin >> port;
	LOG(INFO, "ServerBoard::Client() " << "Port: " << port);
	cout << endl;

	if ((Connect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
		cout << "socket() failed with error code." << endl;
		LOG(INFO,
				"ServerBoard::Client() " << "socket() failed with error code.");

	}

	memset((char *) &ClientAddr, 0, sizeof(ClientAddr));

	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(port);
#ifdef _WIN32
	ClientAddr.sin_addr.S_un.S_addr = inet_addr(ip);
#else
	ClientAddr.sin_addr.s_addr = inet_addr(ip);
#endif

	while (true) {

		sendto(Connect, connected, BUFLEN, 0, (struct sockaddr *) &ClientAddr,
				addrLen);

		if (sendto(Connect, message, BUFLEN, 0, (struct sockaddr *) &ClientAddr,
				addrLen) == SOCKET_ERROR) {
			cout << "sendto() failed with error code." << endl;
			LOG(INFO,
					"ServerBoard::Client() " << "sendto() failed with error code.");
		}

		if (recvfrom(Connect, buffer, BUFLEN, 0,
				(struct sockaddr *) &ClientAddr, &addrLen) == SOCKET_ERROR) {
			cout << "recvfrom() failed with error code." << endl;
			LOG(INFO,
					"ServerBoard::Client() " << "recvfrom() failed with error code.");
		} else {
			cout << buffer << endl;
			LOG(INFO, "ServerBoard::Client() " << buffer);
		}

		break;
	}

	cout << endl << endl;
	cout << "[1] Create Game\n" << "[2] Join Game\n" << "[3] Back\n" << endl;
	cout << "Enter your option: ";

#ifdef _WIN32
	closesocket(Connect);
	WSACleanup();
	LOG(INFO, "ServerBoard::Client() " << "Close socket");
#else
	close(Connect);
	LOG(INFO, "ServerBoard::Client() " << "Close socket" );
#endif

}

ClientBoard::~ClientBoard() {
}

