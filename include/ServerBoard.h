#ifndef SERVERBOARD_H_
#define SERVERBOARD_H_
#include "Board.h"


class ServerBoard : public Board {
public:
	ServerBoard();
	void Server();
	virtual ~ServerBoard();

private:

};

#endif