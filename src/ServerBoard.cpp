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
#include<iostream>

const int BUFLEN = 1024;
const int PORT = 9999;

using namespace std;

ServerBoard::ServerBoard() :
		Board(name) {
}

void ServerBoard::Server() {

#ifdef _WIN32
	WSADATA Wsa;
	WORD Version = MAKEWORD(2, 1);
#endif

	struct sockaddr_in ServerAddr;
	struct sockaddr_in ClientAddr;

	int Listen;

	char buffer[BUFLEN];
	char message[BUFLEN];
	char connected[BUFLEN] = "Message from server: Connection completed.";
	int addrLen;
	int recvLen;

	addrLen = sizeof(ClientAddr);

	cout << "Server: " << endl;

#ifdef _WIN32
	if (WSAStartup(Version, &Wsa) != 0) {
		cout << "Startup error." << endl;
		LOG(INFO, "ServerBoard::Server() " << "Windows startup error.");
	}
#endif

	cout << "Initialized.";
	LOG(INFO, "ServerBoard::Server() " << "Initialized.");

	if ((Listen = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket." << endl;
		LOG(INFO, "ServerBoard::Server() " << "Could not create socket.");
		exit(1);
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
		exit(1);
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
		cin >> message;

		if (sendto(Listen, message, BUFLEN, 0, (struct sockaddr*) &ClientAddr,
				addrLen) == SOCKET_ERROR) {
			cout << "sendto() failed with error code." << endl;
			LOG(INFO,
					"ServerBoard::Server() " << "sendto() failed with error code..");
		}
	}

#ifdef _WIN32
	closesocket(Listen);
	WSACleanup();
	LOG(INFO, "ServerBoard::Server() " << "Close socket");
#else
	close(Listen);
	LOG(INFO, "ServerBoard::Server() " << "Close socket" );
#endif

}

void *ServerBoard::sendMessage(void* arg) {
	cout << "Hello" << endl;
	pthread_exit(0);
	return 0;
}

void ServerBoard::ThreadFunction() {

	struct sockaddr_in ClientAddr;
	int addrLen;
	addrLen = sizeof(ClientAddr);

	pthread_t sendThread;
	pthread_attr_t attrThread;

	pthread_attr_init(&attrThread);
	pthread_create(&sendThread, &attrThread, &ServerBoard::sendMessage,
			(void*) addrLen);
	pthread_join(sendThread, NULL);
}
ServerBoard::~ServerBoard() {

}

