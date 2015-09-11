#ifndef CLIENTBOARD_H_
#define CLIENTBOARD_H_
#include "Board.h"

class ClientBoard : public IBoard {
public:
	ClientBoard();
	void Client();
	virtual ~ClientBoard();



};

#endif
