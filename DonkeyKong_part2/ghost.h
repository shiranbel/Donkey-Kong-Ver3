#pragma once
#include "enemy.h"

class Ghost : public Enemy{
	
public:
	static constexpr int CHANGE_DIR_PROBABILITY = 5;

	// ctors
	Ghost(Board* pboard) : Enemy(pboard) {
		setPos(pBoard->getStartPosGhost());
		dir = { 1,0 };
		symbol = (char)Board::characters::ghost_s;
	}
	Ghost(Board* pboard, bool skipInit) : Enemy(pboard) {
		if (!skipInit) {
			setPos(pBoard->getStartPosGhost());
		}
	}
	Ghost() {}
										
	bool getRandomBoolean(int num) const;    // get if ghost need change her direction according to probability   
	virtual void move() override;            // changes the barrel's position      
	void checkIsCollision();				 // detects collision with other ghost and change direction
};

