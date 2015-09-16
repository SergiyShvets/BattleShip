#ifndef SERVERBOARD_H_
#define SERVERBOARD_H_

#include "Board.h"
#include "logger.h"

class ServerBoard: public Board {
public:
	ServerBoard();
	void Server();
	bool PlaceShip(Ship &s) {return true;}
	HIT_RESULT Hit(COORDS c){return NO_BOOM;}
	bool AnyAlive() {return true;}
	void Print(){}
	virtual ~ServerBoard();

};

#endif
