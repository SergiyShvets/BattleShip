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

#include<iostream>
#include <stdio.h>
#include <unistd.h>

const int BUFLEN = 1024;
const int MAX_IP_SIZE = 15;

using namespace std;

ClientBoard::ClientBoard() :
		IBoard() {

}

void ClientBoard::Client() {

#ifdef _WIN32
	WSADATA Wsa;
	WORD Version = MAKEWORD(2, 1);
#endif

	struct sockaddr_in ClientAddr;

	SOCKET Connect;

	int Len;
	char buffer[BUFLEN];
	char message[BUFLEN];
	char greeting[BUFLEN] = "Message from client: Client connected.";
	char ip[MAX_IP_SIZE];
	short port;

	Len = sizeof(ClientAddr);

	cout << "Client:" << endl;

	cout << "Enter IP: ";
	cin >> ip;
	LOG(INFO, "ServerBoard::Client() " << "IP: " << ip );
	cout << "Enter Port: ";
	cin >> port;
	LOG(INFO, "ServerBoard::Client() " << "Port: " << port );
	cout << endl;

#ifdef _WIN32
	if (WSAStartup(Version, &Wsa) != 0) {
		cout << "Startup error." << endl;
		LOG(INFO, "ServerBoard::Client() " << "Windows startup error." );
		exit(1);
	}
#endif

	if ((Connect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
		cout << "socket() failed with error code." << endl;
		LOG(INFO, "ServerBoard::Client() " << "socket() failed with error code." );
		exit(1);
	}

	memset((char *) &ClientAddr, 0, sizeof(ClientAddr));

	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(port);
	ClientAddr.sin_addr.S_un.S_addr = inet_addr(ip);

	while (true) {

		sendto(Connect, greeting, BUFLEN, 0,
						(struct sockaddr *) &ClientAddr, Len);


		if (sendto(Connect, message, BUFLEN, 0,
				(struct sockaddr *) &ClientAddr, Len) == SOCKET_ERROR) {
			cout << "sendto() failed with error code." << endl;
			LOG(INFO, "ServerBoard::Client() " << "sendto() failed with error code." );
		}

		if (recvfrom(Connect, buffer, BUFLEN, 0,
				(struct sockaddr *) &ClientAddr, &Len) == SOCKET_ERROR) {
			cout << "recvfrom() failed with error code." << endl;
			LOG(INFO, "ServerBoard::Client() " << "recvfrom() failed with error code." );
		}else {
			cout << buffer << endl;
			LOG(INFO, "ServerBoard::Client() " << buffer );
			}
	}

#ifdef _WIN32
	closesocket(Connect);
	WSACleanup();
	system("pause");
	LOG(INFO, "ServerBoard::Client() " << "Close socket" );
#else
	close(Connect);
	LOG(INFO, "ServerBoard::Client() " << "Close socket" );
#endif

}

ClientBoard::~ClientBoard() {
}

