#ifndef SHIPS_H_
#define SHIPS_H_

typedef struct {
	unsigned int x;
	unsigned int y;
} COORDS;

typedef enum {
	NO_BOOM, BOOM, WAS_HIT
} HIT_RESULT;

#define BOARD_DIM 10

#endif
