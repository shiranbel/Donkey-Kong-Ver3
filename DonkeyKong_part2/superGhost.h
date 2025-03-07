#pragma once
#include "ghost.h"
#include "enemy.h"
#include "position.h"


class SuperGhost : public Ghost
{
public:
	// ctor
	SuperGhost(Board* pboard) : Ghost(pboard, true) {
		setPos(pBoard->getStartPosSuperGhost());
		dir = { 1,0 };
		symbol = (char)Board::characters::ghost_l;
	}
	SuperGhost(){}

	virtual void move() override;	// super ghost movement
};

