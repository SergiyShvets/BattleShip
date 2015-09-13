#ifndef SHIP_H_
#define SHIP_H_

#include "Ships.h"

#include <vector>
#include <string>

typedef enum {
	SUB = 1, DES = 2, CRU = 3, CAR = 4,
} SHIP_TYPE;

typedef enum {
	VERT, HOR,
} POSITION;

class Ship {
public:
	Ship(SHIP_TYPE type, COORDS coord, POSITION pos);
	virtual ~Ship();
	SHIP_TYPE GetType() const {
		return type;
	}
	POSITION GetPos() const {
		return pos;
	}
	COORDS GetCoord() const {
		return coord;
	}
	int GetDecks() const {
		return validDecks;
	}
private:
	POSITION pos;
	SHIP_TYPE type;
	int validDecks;
	COORDS coord;
};

#endif
