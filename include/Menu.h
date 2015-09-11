#ifndef MENU_H_
#define MENU_H_

#include "ServerBoard.h"
#include "ClientBoard.h"
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Ships.h"
#include <string>

class Menu {
public:
	Menu();

	void LoadTitle();
	int MainMenu();

	virtual ~Menu();
private:

	int NewGame(int &option);
	int ReadOption(int &option);
	void GameRun();
	void Rules();
	void Server();
	void Connect();
	ClientBoard *clientBoard;
	ServerBoard *serverBoard;
};

#endif
