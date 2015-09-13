#include "Player.h"
#include "logger.h"

#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

const int DUO = 2;

string head = "Head";
string tail = "Tail";
string cru = "Crusier(4)  ";
string car = "Carrier(3)  ";
string des = "Destroyer(2)";
string sub = "Submarine(1)";
string hor = "Horizontal";
string vert = "Vertical  ";

Player::Player(string n) :
		name(n) {
	srand(static_cast<unsigned int>(time(NULL)));
}

Player::~Player() {

}

bool Player::DecideWhoseHit() {

	bool winner = 0;
	int result = 0;
	int choice;
	cout << " Throw a coin" << endl;
	cout << ' ' << name << " choose [1]" << head << " or [2]" << tail << ":"
			<< endl;
	cout << ' ';

	cin >> choice;

	result = static_cast<COIN>(rand() % DUO);

	switch (result) {
	case HEAD:

		if (choice == 1) {
			cout << ' ' << name << " has chosen " << head << endl;
			LOG(INFO,
					"Player::DecideWhoseHit(): " << name << " has chosen " << head);
			winner = true;
		} else if (choice == 2) {
			cout << ' ' << name << " has chosen " << tail << endl;
			LOG(INFO,
					"Player::DecideWhoseHit(): " << name << " has chosen " << tail);
			winner = false;
		} else {
			cout << ' ' << name << " has chosen a rib of coin" << endl;
			LOG(INFO,
					"Player::DecideWhoseHit(): " << name << " has chosen wrong option");
		}
		sleep(1);
		cout << " (H)\n" << " Fell " << head << endl;
		LOG(INFO, "Player::DecideWhoseHit(): " << "Fell (H) " << head <<'\n');
		break;

	case TAIL:

		if (choice == 2) {
			cout << ' ' << name << " has chosen " << tail << endl;
			LOG(INFO,
					"Player::DecideWhoseHit(): " << name << " has chosen " << tail);
			winner = true;
		} else if (choice == 1) {
			cout << ' ' << name << " has chosen " << head << endl;
			LOG(INFO,
					"Player::DecideWhoseHit(): " << name << " has chosen " << head);
			winner = false;
		} else {
			cout << ' ' << name << " has chosen a rib of coin" << endl;
			LOG(INFO,
					"Player::DecideWhoseHit(): " << name << " has chosen wrong option");
		}
		sleep(1);
		cout << " (T)\n" << " Fell " << tail << endl;
		LOG(INFO, "Player::DecideWhoseHit(): "<< "Fell (T) " << tail <<'\n');
		break;

	default:
		cout << " collapse" << endl;
		break;
	}

	sleep(1);
	return winner;
}

bool Player::MakeTurn(Board& board, COORDS c) {

	return board.Hit(c) != NO_BOOM;
}

void Player::PlaceShips(Board& board) {

	COORDS c;
	POSITION pos;
	SHIP_TYPE shipsToPlace[BOARD_DIM] = { CAR, CRU, CRU, DES, DES, DES, SUB,
			SUB, SUB, SUB };

	for (unsigned int i = 0; i < sizeof(shipsToPlace) / sizeof(shipsToPlace[0]);
			) {
		c.x = rand() % BOARD_DIM;
		c.y = rand() % BOARD_DIM;

		pos = static_cast<POSITION>(rand() % DUO);

		Ship ships(shipsToPlace[i], c, pos);

		if (board.PlaceShip(ships)) {

			string shipName;

			switch (shipsToPlace[i]) {
			case 4:
				shipName = cru;
				break;
			case 3:
				shipName = car;
				break;
			case 2:
				shipName = des;
				break;
			case 1:
				shipName = sub;
				break;
			default:
				cout << "Error ship name" << endl;
				break;
			}

			string position;

			switch (pos) {
			case 0:
				position = vert;
				break;
			case 1:
				position = hor;
				break;
			default:
				cout << "Error ship pos" << endl;
				break;
			}

			LOG(INFO,
					"Player::PlaceShips(board): " << name <<" placed "<< '"' << shipName << '"' << " at position - " << position << " coords: " << c.x << ":" << c.y);
			i++;
		}
	}
	LOG(INFO, " ");
	cout << endl;
}

int Player::InputCoordX(COORDS &c) {

	cout << " Press [#] to give up." << endl;
	cout << ' ' << name << " Enter X(0-9) - Y(A-J) coordinates:" << endl;
	cout << ' ';

	INPUT input;

	for (int i = 0; i < BOARD_DIM; i++) {
		c.x = input.xDigits[i];
		cin >> input.xDigits[i];

		switch (input.xDigits[i]) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case '#':
			cout << " Give up!" << endl;
			cout << ' ' << name << " has lost" << endl;
			sleep(2);
			MainMenu();
		default:
			cout << " ERROR - wrong Xcoord, please try again:" << endl;
			cout << ' ';
			continue;
		}
	}
	return c.x;
}

int Player::InputCoordY(COORDS &c) {

	INPUT input;

	for (int i = 0; i < BOARD_DIM; i++) {

		c.y = input.yChars[i];
		cin >> input.yChars[i];

		switch (input.yChars[i]) {
		case 'A':
		case 'a':
			return 0;
		case 'B':
		case 'b':
			return 1;
		case 'C':
		case 'c':
			return 2;
		case 'D':
		case 'd':
			return 3;
		case 'E':
		case 'e':
			return 4;
		case 'F':
		case 'f':
			return 5;
		case 'G':
		case 'g':
			return 6;
		case 'H':
		case 'h':
			return 7;
		case 'I':
		case 'i':
			return 8;
		case 'J':
		case 'j':
			return 9;
		default:
			cout << " ERROR - wrong Ycoord, please try again:" << endl;
			cout << ' ';
			continue;
		}
	}
	return c.y;
}

void Player::MainMenu() {
	Menu m;
	m.MainMenu();
}
std::string Player::GetName() {
	return name;
}
