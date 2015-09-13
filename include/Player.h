#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"
#include "Menu.h"
#include "Game.h"
#include "Ship.h"
#include "Ships.h"

#include <string>

typedef struct {
	char xDigits[BOARD_DIM];
	char yChars[BOARD_DIM];
} INPUT;

typedef enum {
	HEAD, TAIL
} COIN;

class Player {

public:
	Player(std::string name);
	bool DecideWhoseHit();
	bool MakeTurn(Board& board, COORDS hit);
	void PlaceShips(Board& board);
	int InputCoordX(COORDS &c);
	int InputCoordY(COORDS &c);
	std::string GetName();
	void MainMenu();
	virtual ~Player();
private:
	std::string name;
};

#endif
