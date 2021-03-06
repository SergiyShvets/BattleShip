#include "ServerBoard.h"

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <pthread.h>
#include <iostream>
#include <cstdlib>

const int BUFLEN = 1024;
const int PORT = 9999;

#ifndef SOCKET_ERROR
    #define SOCKET_ERROR -1
	#define INVALID_SOCKET 0;
#endif

using namespace std;

ServerBoard::ServerBoard() :
		Board(name) {
}

void ServerBoard::Server() {

	struct sockaddr_in ServerAddr;
	struct sockaddr_in ClientAddr;

	int Listen;

	char buffer[BUFLEN];
	char message[BUFLEN];
	const char connected[BUFLEN] = "Message from server: Connection completed.";
	int addrLen;
	int recvLen;

	addrLen = sizeof(ClientAddr);

	cout << "Server: " << endl;

	cout << "Initialized.";
	LOG(INFO, "ServerBoard::Server() " << "Initialized.");

	if ((Listen = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket." << endl;
		LOG(INFO, "ServerBoard::Server() " << "Could not create socket.");

	} else {

		cout << " Socket created.";
		LOG(INFO, "ServerBoard::Server() " << "Socket created.");
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(PORT);

	if (bind(Listen, (sockaddr*) &ServerAddr,
			sizeof(ServerAddr)) == SOCKET_ERROR) {
		cout << "Bind Failed." << endl;
		LOG(INFO, "ServerBoard::Server() " << "Bind failed.");

	} else {

		cout << " Bind Done." << endl;
		LOG(INFO, "ServerBoard::Server() " << "Bind Done.");
	}

	cout << "Waiting for client...\n " << endl;

	while (true) {

		if ((recvLen = recvfrom(Listen, buffer, BUFLEN, 0,
				(struct sockaddr *) &ClientAddr, &addrLen)) == SOCKET_ERROR) {
			cout << "recvfrom() failed with error code." << endl;
			LOG(INFO,
					"ServerBoard::Server() " << "recvfrom() failed with error code.");
		} else {
			cout << buffer << endl;
			LOG(INFO, "ServerBoard::Server() " << buffer);
		}

		sendto(Listen, connected, BUFLEN, 0, (struct sockaddr *) &ClientAddr,
				addrLen);


		if (sendto(Listen, message, BUFLEN, 0, (struct sockaddr*) &ClientAddr,
				addrLen) == SOCKET_ERROR) {
			cout << "sendto() failed with error code." << endl;
			LOG(INFO,
					"ServerBoard::Server() " << "sendto() failed with error code..");
		}
		break;
	}
	cout << endl << endl;
	cout << "[1] Create Game\n" << "[2] Join Game\n" << "[3] Back\n" << endl;
	cout << "Enter your option: ";

#ifdef _WIN32
	closesocket(Listen);
#else
	close(Listen);
	LOG(INFO, "ServerBoard::Server() " << "Close socket" );
#endif

}

ServerBoard::~ServerBoard() {

}

