
#include "Ship.h"

Ship::Ship(SHIP_TYPE type, COORDS coord, POSITION pos) {

	this->type = type;

	switch (type) {

	case SUB:
		validDecks = 1;
		break;
	case DES:
		validDecks = 2;
		break;
	case CRU:
		validDecks = 3;
		break;
	case CAR:
		validDecks = 4;
		break;
	default:
		validDecks = 0;
	}

	this->coord = coord;
	this->pos = pos;
}

Ship::~Ship() {

}

