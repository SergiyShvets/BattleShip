#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Menu.h"
#include "logger.h"

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

using namespace std;

void clear()
{
#ifdef _WIN32
	system ("cls");
#else
	system("clear");
#endif
}

Game::Game() {
	srand( static_cast<unsigned int>(time(NULL)) );
}

void Game::Run()
{
	Player p1("Sergiy"), p2("Kostya");
	Board b1("Board of Sergiy"), b2("Board of Kostya");
	Menu m;

	LOG(INFO,"Game::Run(): " <<"Player1 " << p1.GetName());
	LOG(INFO,"Game::Run(): " <<"Player2 " << p2.GetName() << '\n');

	COORDS c;

	Player *pActivePlayer = &p1;
	Board  *bActiveBoard = &b2;
/*
	if(pActivePlayer->DecideWhoseHit()){
		cout << " Win :)" << endl;
		cout <<' '<< p1.GetName() << " will hit first" << endl;
		pActivePlayer = &p1;
		bActiveBoard = &b2;
		LOG(INFO,"Game::Run(): "  << pActivePlayer->GetName() << " wins, his hit first\n");
	}else{
		cout << " Loose :(" << endl;
		cout <<' '<< p2.GetName() << " will hit first" << endl;
		pActivePlayer = &p2;
		bActiveBoard = &b1;
		LOG(INFO,"Game::Run(): "  << pActivePlayer->GetName() << " wins, his hit first\n");
	}

	sleep(2);
	clear();
*/
	p1.PlaceShips(b1);
	p2.PlaceShips(b2);

	b1.Print();
	b2.Print();


	while(b1.AnyAlive()  && b2.AnyAlive() ) {
/*
		c.x = pActivePlayer->InputCoordX(c);
		c.y = pActivePlayer->InputCoordY(c);
*/
		c.x = rand()%10;
		c.y = rand()%10;

		if(!pActivePlayer->MakeTurn(*bActiveBoard, c))
		{
			bActiveBoard = (bActiveBoard == &b2 ? &b1:&b2);
			pActivePlayer = (pActivePlayer == &p1 ? &p2:&p1);
		}

		cout << endl;

	//	sleep(1);
	//	clear();
		b1.Print();
		b2.Print();
	//	sleep(1);
	}
	LOG(INFO," ");
	if(!b1.AnyAlive() ){
		cout << " Player " << p2.GetName() << " has won" << endl;
		LOG(INFO,"Game::Run(): "<< " Player " << p2.GetName() << " has won" << '\n');
	}else{
		cout << " Player " << p1.GetName() << " has won" << endl;
		LOG(INFO,"Game::Run(): "<< " Player " << p1.GetName() << " has won" << '\n');
	}

	sleep(1);
	cout << " GAME OVER" << endl;
	sleep(3);

    m.MainMenu();
}

Game::~Game() {

}



