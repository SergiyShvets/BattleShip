#ifndef SERVERBOARD_H_
#define SERVERBOARD_H_

#include "Board.h"
#include "logger.h"

class ServerBoard: public Board {
public:
	ServerBoard();
	void Server();
	virtual bool PlaceShip(Ship &s) {return true;}
	virtual HIT_RESULT Hit(COORDS c){return NO_BOOM;}
	virtual bool AnyAlive() {return true;}
	virtual void Print(){}
	virtual ~ServerBoard();

};

#endif
