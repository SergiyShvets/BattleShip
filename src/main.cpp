#include "Game.h"
#include "Menu.h"
#include "logger.h"
#include "WinSock.h"

#define AAP_NAME "Ships"
using namespace std;

int main() {

	Logger::Open(AAP_NAME ".log", DBG, 1000000);
	LOG(INFO, "main(): Game start" << '\n');

	WinSock ws;
	ws.StartUp();
	Menu m;
	m.MainMenu();
	ws.~WinSock();

	LOG(INFO, "main(): Game over");
	Logger::Close();
	return 0;
}
