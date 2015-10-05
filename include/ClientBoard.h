#ifndef CLIENTBOARD_H_
#define CLIENTBOARD_H_

#include "Board.h"
#include "logger.h"

class ClientBoard: public IBoard {
public:
	ClientBoard();
	void Client();
	virtual bool PlaceShip(Ship &s) {return true;}
	virtual HIT_RESULT Hit(COORDS c){return NO_BOOM;}
	virtual bool AnyAlive() {return true;}
	virtual void Print(){}
	virtual ~ClientBoard();
};

#endif
