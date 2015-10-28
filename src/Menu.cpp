#include "Menu.h"

#include <unistd.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

string title = "\n\n\n\t\t\t Battleships";

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

Menu::Menu() :
		clientBoard(), serverBoard(), option() {

}

void Menu::LoadTitle() {

	string loading = "\n\n\n\n\n\t\t\t LOADING...";
	string welcome = "\n\n\n\n\n\t\t      WELCOME TO BATTLESHIPS";
	cout << ' ' << loading;
	sleep(1);
	clearScreen();
	cout << loading << "7%";
	sleep(1);
	clearScreen();
	cout << loading << "34%";
	sleep(1);
	clearScreen();
	cout << loading << "51%";
	sleep(1);
	clearScreen();
	cout << loading << "79%";
	sleep(1);
	clearScreen();
	cout << loading << "100%" << endl;
	sleep(1);
	clearScreen();

	cout << welcome << endl;
	sleep(2);
	clearScreen();
}

int Menu::MainMenu() {

	int option;

	string newGame = "\t\t\t [1] New Game";
	string localGame = "\t\t\t [2] Local Game";
	string rules = "\t\t\t [3] Show Rules";
	string exit = "\t\t\t [4] Exit to Desktop";
	clearScreen();
	cout << title << endl << endl;
	cout << newGame << endl;
	cout << localGame << endl;
	cout << rules << endl;
	cout << exit << endl << endl;
	cout << "\t\t         Enter your option(1-4): ";
	option = ReadOption(option);
	return option;
}

int Menu::ReadOption(int &option) {

	char choseOption[BOARD_DIM] = { '1', '2', '3', '4' };
	string result;

	for (int i = 0; i < BOARD_DIM; i++) {
		option = choseOption[i];
		cin >> choseOption[i];
		switch (choseOption[i]) {
		case '1':
			clearScreen();
			GameRun();
			break;
		case '2':
			clearScreen();
			NewGameMenu(option);
			break;
		case '3':
			clearScreen();
			Rules();
			break;
		case '4':
			cout << "\n\t\t\t Closing the game..." << endl;
			sleep(1);
			exit(1);
			break;
		default:
			cout
					<< "\n\t\t         You have entered wrong option\n\t\t         please try again:";

			continue;
		}
	}
	return option;
}

void Menu::Rules() {

	cout << "Rules:\n";
	cout << "There is a 10 x 10 grid for each player\n";
	cout << "Each grid has different ships on it, all of different sizes\n";
	cout << "Each player guesses a position on the opponent's grid\n";
	cout << "If there is a ship on that exact position, it is a hit\n";
	cout << "If the player hits every position on a ship, it is sunk.\n";
	cout
			<< "Once a player sinks every ship on their opponent's grid, they win\n";
	cout << "Players take turns guessing on each other's board\n";
	cout << "Hope you have fun, good luck!\n\n";
	cout << "\n\n\n\n[1] Back" << endl;
	char optionBack;
	cin >> optionBack;
	if (optionBack == 1)
		MainMenu();
	else
		MainMenu();
	LOG(INFO, "Menu::Rules: " <<"Back");
}

int Menu::NewGameMenu(int &option) {

	string create = "\t\t\t [1] Create Game";
	string join = "\t\t\t [2] Join Game";
	string back = "\t\t\t [3] Back";
	clearScreen();

	cout << title << endl;
	cout << endl;
	cout << create << endl;
	cout << join << endl;
	cout << back << endl << endl;
	cout << "\t\t         Enter your option(1-3): ";

	char choseOption[BOARD_DIM] = { '1', '2', '3' };
	for (int i = 0; i < BOARD_DIM; i++) {
		option = choseOption[i];
		cin >> choseOption[i];
		switch (choseOption[i]) {
		case '1':
			clearScreen();
			Server();
			break;
		case '2':
			clearScreen();
			Connect();
			break;
		case '3':
			MainMenu();
			break;
		default:
			cout
					<< "\n\t\t    Error - You entered wrong option\n \t\t    please try again:";
			continue;
		}
	}
	return option;
}

void Menu::GameRun() {
	Game g;
	g.Run();
}

void Menu::Server() {

	serverBoard->Server();
}

void Menu::Connect() {

	clientBoard->Client();
}

Menu::~Menu() {

}

