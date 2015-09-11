#include "ServerBoard.h"

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
#include <unistd.h>

const int BUFLEN = 1024;
const int PORT = 9999;

using namespace std;

ServerBoard::ServerBoard():Board(name){

}

void ServerBoard::Server(){

#ifdef _WIN32
	WSADATA Wsa;
	WORD Version = MAKEWORD(2, 1);
#endif

	SOCKET Listen;

	struct sockaddr_in ServerAddr;
	struct sockaddr_in ClientAddr;

	char buffer[BUFLEN];

	int Len;
	int recvLen;

	Len = sizeof(ClientAddr);

	cout << "Server: ";

#ifdef _WIN32
	if (WSAStartup(Version, &Wsa) != 0) {
		cout << "Startup error." << endl;
		exit(1);
	}
#endif
		sleep(1);
		cout << "Initialized.";

	if ((Listen = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket." << endl;
		exit(1);
	} else {
		sleep(1);
		cout << " Socket created.";
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(PORT);

	if (bind(Listen, (sockaddr*) &ServerAddr,
			sizeof(ServerAddr)) == SOCKET_ERROR) {
		cout << "Bind Failed." << endl;
		exit(1);
	} else{
		sleep(1);
		cout << " Bind Done." << endl;
	cout << endl;
	}
	sleep(1);
	cout << "Looking for client...\n " << endl;

	while (true) {

		memset(buffer, '\0', BUFLEN);

		if ((recvLen = recvfrom(Listen, buffer, BUFLEN, 0,
				(struct sockaddr *) &ClientAddr, &Len)) == SOCKET_ERROR) {
			cout << "recvfrom() failed with error code." << endl;
			exit(1);
		} else {
		cout << "Received packet from : " << inet_ntoa(ClientAddr.sin_addr)
				<< ntohs(ClientAddr.sin_port) << endl;
		break;
		}

		if (sendto(Listen, buffer, recvLen, 0, (struct sockaddr*) &ClientAddr,
				Len) == SOCKET_ERROR) {
			cout << "sendto() failed with error code." << endl;
			exit(1);
		}
	}

#ifdef _WIN32
	closesocket(Listen);
	WSACleanup();
	system("pause");
#else
	close(Listen);
#endif

}

ServerBoard::~ServerBoard() {

}

