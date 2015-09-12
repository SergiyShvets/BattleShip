#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Ship.h"
#include "Ships.h"

class Game {
public:
	Game();
	void Run ();
	virtual ~Game();
};

#endif
