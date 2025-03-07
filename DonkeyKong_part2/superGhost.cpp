#include "superGhost.h"
#include "ghost.h"

// this function handles super ghost movement
void SuperGhost::move() {
	Position currPos = getPosition();
	Position newPos = { currPos.getX() + dir.x, currPos.getY() + dir.y };                     // get the next position of the barrel
	char next_pos_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY());                 // gets the next position's char
	char curr_pos_ch_under = pBoard->getCharFromCurr(currPos.getX(), currPos.getY() + 1);     // gets the char below the next position
	char next_pos_ch_under = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY() + 1);   // gets the next char below the next position

	// if the ghost's curr position under is at the border and the new Y-coordinate is within the screen height
	if (curr_pos_ch_under == Board::SPACE && newPos.getY() < GameConfig::MAX_HEIGHT) {
		dir = { 0,1 };    // free fall
		setPos(newPos);
		return;
	}

	// climb : super ghost wil always climb
	char curr_pos_char = pBoard->getCharFromCurr(currPos.getX(), currPos.getY());
	if (curr_pos_char == (char)Board::Floor_chars::ladder)  {
		dir = { 0,-1 };
		Position newPos = { currPos.getX() + dir.x, currPos.getY() + dir.y };
		setPos(newPos);
		return;
	}
	if (dir.y == -1 && curr_pos_char == Board::SPACE) {
		dir = { 1,0 };
		return;
	}

	// go down - super ghost can randolmy go down the ladder
	char curr_pos_char_2xUnder = pBoard->getCharFromCurr(currPos.getX(), currPos.getY() + 2);
	if (curr_pos_char_2xUnder == (char)Board::Floor_chars::ladder && getRandomBoolean(10)) {
		dir = { 0, 1 };
		Position newPos = { currPos.getX() + dir.x, currPos.getY() + dir.y };
		setPos(newPos);
		return;
	}
	if (dir.y == 1 && isOnFloor(curr_pos_ch_under)) {
		dir = { 1,0 };
		return;
	}

	if (dir.y == 1) {	// when the ghost is falling 
		// if next ghost's pos is on floor or out border high
		if (isOnFloor(next_pos_ch) || newPos.getY() >= GameConfig::MAX_HEIGHT) {
			dir = { 1, 0 };
			return;		// finish here
		}
	}

	// check for wall or specific character
	if (isOnFloor(next_pos_ch) || next_pos_ch_under == Board::SPACE || newPos.getX() >= GameConfig::MAX_WIDTH) {
		dir.x *= -1; // change direction
		return;
	}
	if (getRandomBoolean(Ghost::CHANGE_DIR_PROBABILITY)) {
		dir.x *= -1; // change direction
		return;
	}
	setPos(newPos);    // set position
}