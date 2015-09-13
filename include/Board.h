#ifndef BOARD_H_
#define BOARD_H_

#include "Ships.h"
#include "Ship.h"

#include <vector>
#include <string>

typedef enum {
	EMPTY, MISS, HITDECK, DECK,
} CELL_STATE;

typedef struct {
	CELL_STATE state;
} Cell;

class IBoard {
public:
	virtual bool PlaceShip(Ship &s) = 0;
	virtual HIT_RESULT Hit(COORDS c) = 0;
	virtual bool AnyAlive() = 0;
	virtual void Print() = 0;
	virtual ~IBoard();
};

class Board: IBoard {
public:
	Board(std::string name);
	bool PlaceShip(Ship &s);
	HIT_RESULT Hit(COORDS c);
	bool AnyAlive();
	void Print();
	virtual ~Board();
protected:
	bool CheckValidPlace(Ship &s);
	bool CheckBoardBorder(Ship &s);
	bool CheckValidHit(COORDS c);
	std::string name;
private:
	Cell sea[BOARD_DIM][BOARD_DIM];
};

#endif
