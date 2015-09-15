#ifndef CLIENTBOARD_H_
#define CLIENTBOARD_H_

#include "Board.h"
#include "logger.h"

class ClientBoard: public IBoard {
public:
	ClientBoard();
	void Client();
	bool PlaceShip(Ship &s) {return true;}
	HIT_RESULT Hit(COORDS c){return NO_BOOM;}
	bool AnyAlive() {return true;}
	void Print(){}
	virtual ~ClientBoard();
};

#endif
