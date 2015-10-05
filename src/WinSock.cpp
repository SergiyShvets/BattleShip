#include "WinSock.h"
#include "logger.h"

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#endif

#include <iostream>

using namespace std;

WinSock::WinSock() {

}

void WinSock::StartUp() {
#ifdef _WIN32
	WSADATA Wsa;
	WORD Version = MAKEWORD(2, 1);

	if (WSAStartup(Version, &Wsa) != 0) {
		cout << "Startup error." << endl;
		LOG(INFO, "WinSock::WinSock " << "Windows startup error.");
	}
#endif
}

WinSock::~WinSock() {
#ifdef _WIN32
	WSACleanup();
	LOG(INFO, "ServerBoard::Server() " << "Close socket");
#endif
}

