#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "logger.h"
#include <pthread.h>

using namespace std;

string colY = "  #|A|B|C|D|E|F|G|H|I|J|";
string rowX = "|";
string line = "  ======================";

char empty = ' ';
char miss = 'o';
char deck = '$';
char hitdeck = 'X';
char outboard = 'F';

const int MIN_COORD = 0;
const int MAX_COORD = 9;
const int DISTANCE = 1;

Board::Board(std::string n) :
		name(n) {

	sea.resize(BOARD_DIM);
	for (int x = 0; x < BOARD_DIM; x++) {
		sea[x].resize(BOARD_DIM);
		for (int y = 0; y < BOARD_DIM; y++) {
			sea[x][y].state = EMPTY;
		}
	}
}

bool Board::CheckValidPlace(Ship &s) {

	bool validCell = true;

	int pos = s.GetPos();
	int x0 = s.GetCoord().x;
	int y0 = s.GetCoord().y;
	int decks = s.GetDecks();

	for (int x = x0 - DISTANCE; x <= x0 + DISTANCE; x++) {
		for (int y = y0 - DISTANCE; y <= y0 + DISTANCE; y++) {
			if (x < MIN_COORD || x > MAX_COORD || y < MIN_COORD
					|| y > MAX_COORD)
				continue;

			switch (pos) {
			case VERT:
				if (sea[x][y].state == DECK) {
					validCell = false;
				}
				if (sea[x0 + decks][y].state == DECK) {
					validCell = false;
				}
				for (int j = 0; j < decks; j++) {
					if (sea[x0 + j][y].state != EMPTY) {
						validCell = false;
					}
				}
				break;
			case HOR:
				if (sea[x][y].state == DECK) {
					validCell = false;
				}
				if (sea[x][y0 + decks].state == DECK) {
					validCell = false;
				}

				for (int j = 0; j < decks; j++) {
					if (sea[x][y0 + j].state != EMPTY) {
						validCell = false;
					}
				}
				break;
			default:
				validCell = true;
				break;
			}
		}
	}

	return validCell;
}

bool Board::CheckBoardBorder(Ship &s) {

	int x0 = s.GetCoord().x;
	int y0 = s.GetCoord().y;
	int decks = s.GetDecks();
	int pos = s.GetPos();

	if (x0 < MIN_COORD || x0 > MAX_COORD || y0 < MIN_COORD || y0 > MAX_COORD)
		return false;

	switch (pos) {
	case VERT:
		if (x0 + decks < MIN_COORD)
			return false;
		if (x0 + decks > MAX_COORD)
			return false;
		break;
	case HOR:
		if (y0 + decks < MIN_COORD)
			return false;
		if (y0 + decks > MAX_COORD)
			return false;
		break;
	default:
		return true;
	}
	return true;
}

bool Board::PlaceShip(Ship& s) {

	int x0 = s.GetCoord().x;
	int y0 = s.GetCoord().y;
	int decks = s.GetDecks();
	int pos = s.GetPos();

	if (!CheckBoardBorder(s) || !CheckValidPlace(s))
		return false;

	if (pos == VERT) {
		for (int i = 0; i < decks; i++) {
			sea[x0 + i][y0].state = DECK;
		}
	} else {
		for (int i = 0; i < decks; i++) {
			sea[x0][y0 + i].state = DECK;
		}
	}

	return true;
}

bool Board::CheckValidHit(COORDS c) {

	if (sea[c.x][c.y].state != MISS && sea[c.x][c.y].state != HITDECK)
		return true;
	return false;
}

HIT_RESULT Board::Hit(COORDS c) {

	if (CheckValidHit(c)) {

		if (sea[c.x][c.y].state == EMPTY) {
			sea[c.x][c.y].state = MISS;
			cout << " Miss!" << endl;
			LOG(INFO,
					"Board::Hit(c):" << name <<" X:" << c.x << " Y:" << c.y << " result - Miss");
			return NO_BOOM;

		} else if (sea[c.x][c.y].state == DECK) {
			sea[c.x][c.y].state = HITDECK;
			cout << " Hit!!!" << endl;
			LOG(INFO,
					"Board::Hit(c):" << name <<" X:" << c.x << " Y:" << c.y << " result - Hit");
			}
			return BOOM;

	} else {
		cout << " You had already shot there \n please try again:" << endl;
		LOG(INFO,
				"Board::Hit(c):" << name <<" X:" << c.x << " Y:" << c.y << " result - Error");
		return WAS_HIT;
	}

	return NO_BOOM;
}

bool Board::AnyAlive() {

	for (int x = 0; x < BOARD_DIM; x++) {
		for (int y = 0; y < BOARD_DIM; y++) {
			if (sea[x][y].state == DECK)
				return true;
		}
	}

	return false;
}

void Board::Print() {

	cout << line << endl;
	cout << " This is '" << name << "'" << endl;
	cout << line << endl;

	char mark;

	cout << colY << endl;

	for (int x = 0; x < BOARD_DIM; x++) {
		cout << "  " << x << rowX;
		for (int y = 0; y < BOARD_DIM; y++) {
			switch (sea[x][y].state) {
			case EMPTY:
				mark = empty;
				break;
			case MISS:
				mark = miss;
				break;
			case HITDECK:
				mark = hitdeck;
				break;
			case DECK:
				mark = deck;
				break;
			default:
				mark = outboard;
			}
			cout << mark << rowX;
		}
		cout << endl;
	}
	cout << line << endl;
	cout << endl;

}

Board::~Board() {

}

IBoard::~IBoard() {

}
