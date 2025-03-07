#include "manualGame.h"
#include "barrel.h"
#include "ghost.h"
#include "hero.h"
#include "superGhost.h"
#include <iostream>
#include <conio.h>

using std::cout;
using std::endl;

// draws all characters to the screen and in current map
void ManualGame::drawAllCharacters(Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, std::vector<SuperGhost>& super_ghosts) const {
	mario.draw();							// draw the hero

	for (auto& ghost : ghosts)              // draw ghosts
		ghost.draw();

	for (auto& super_ghost : super_ghosts)  // draw ghosts
		super_ghost.draw();

	for (auto& barrel : barrels)            // draw barrels
		barrel.draw();
}

// in manual mode we get the input from the user so this function sends the input to mario's movement
bool ManualGame::getInput(Board& board, Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, size_t& iteration, bool with_color, Steps& steps) const {
	if (_kbhit()) {                       // get keyboard clicks
		char key = _getch();
		if (key == ESC) {                 // check if the player pauses
			while (true) {                // play when pressing ESC
				system("cls");
				printPause();
				if (_getch() == ESC) {
					system("cls");
					board.print(with_color,SCREENS_SLEEP_DURATION);
					board.updateLives(mario.getLife());
					board.updateHammer(mario.getWithHammer());
					break;
				}
			}
		}
		if (tolower(key) == NEXT) {       // if user prees next for next level, out of loop
			return false;
		}
		// if mario press p and he have a hammer, let him attack
		if (key == (char)Hero::keys::attack && mario.getWithHammer()) {
			if(isSave)
				steps.addStep(iteration, key);
			mario.attack(ghosts, barrels);
		}

		if (mario.keyPressed(key)) {  // preparing Mario for his next movement based on the key.
			if(isSave)
				steps.addStep(iteration, key);
		}

	}
	return true;
}

// this function updates the results file with hit events in save mode
bool ManualGame::updateHit(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results) {
	if (isSave) 
		results.addResult(iteration, Results::hitBomb);
	return false;
}

// this function introduces the menu to the user with option buttons
void ManualGame::menu() {
	int choice;
	ShowConsoleCursor(false);   // hides cursor
	std::vector<std::string> fileNames = {};

	while (true) {
		// The Menu screen
		gotoxy(0, SCREENS_TOP_MARGIN);
		//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
		cout << "                           WELCOME TO DONKEY KONG GAME!                         " << endl;
		cout << "                                === GAME MENU ===                               " << endl;
		cout << "                           Press:                                               " << endl;
		cout << "                          (1) Start a new game                                  " << endl;
		cout << "                          (2) Start a new game with colors                      " << endl;
		cout << "                          (5) Pick a level                                      " << endl;
		cout << "                          (8) Present instructions and keys                     " << endl;
		cout << "                          (9) EXIT                                              " << endl;
		cout << "                                                                                " << endl;
		std::cout << R"(				       ."`".
				   .-./ _=_ \.-.
				  {  (,(oYo),) }}
				  {{ |   "   |} }
				  { { \(---)/  }}
				  {{  }'-=-'{ } }
				  { { }._:_.{  }}
				  {{  } -:- { } }
				  {_{ }`===`{  _}
				  ((((\)     (/))))" << std::endl;


		choice = _getch();            // user's input
		switch (choice) {
		case NEW_GAME:			      // black and white mode
			system("cls");
			run(false, fileNames);
			break;
		case NEW_GAME_WITH_COLORS:	  // color mode
			system("cls");
			run(true, fileNames);
			break;
		case PICK_A_LEVEL:	          // color mode
			system("cls");
			pickALevel();
			break;
		case INSTRUCTION:			  // instruction screen
			system("cls");
			printInstruction();
			break;
		case EXIT:					  // exit screen
			system("cls");
			printExit();
			return;
		default:
			break;
		}

	}
}

// this function prints the winning screen
void ManualGame::printWinner() const {
	ShowConsoleCursor(false);		// hides cursor
	system("cls");					// erases the screen

	// the victory screen
	gotoxy(0, SCREENS_TOP_MARGIN);
	cout << "	                        == YOU WON!!! ==                         	 " << endl;
	std::cout << R"(                                  ___________
                                 '._==_==_=_.'
                                 .-\:      /-.
                                | (|:.     |) |
                                 '-|:.     |-'
                                   \::.    /
                                    '::. .'
                                      ) (
                                    _.' '._
                                   `"""""""`)" << endl;
	cout << "	                                                                     " << endl;
	cout << "	              \"Oh Mario! You saved me! I LOVE YOU!\"                " << endl;
	cout << "	                  Press ESC to return to menu                        " << endl;

	// returns to menu when pressing ESC
	char ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the game over screen
void ManualGame::printGameOver() const {
	ShowConsoleCursor(false);		// hides the cursor
	char ch;
	system("cls");					// erases the screen

	// exit screen
	gotoxy(0, SCREENS_TOP_MARGIN);
	std::cout << R"(		  __ _  __ _ _ __ ___   ___    _____   _____ _ __ 
		 / _` |/ _` | '_ ` _ \ / _ \  / _ \ \ / / _ \ '__|
		| (_| | (_| | | | | | |  __/ | (_) \ V /  __/ |   
		 \__, |\__,_|_| |_| |_|\___|  \___/ \_/ \___|_|   
		 |___/           
)" << std::endl;
	cout << "                       Don't give up Mario!! Save the princess                  " << endl;
	cout << "                            Press ESC to return to menu                         " << endl;

	// returns to menu when pressing ESC
	ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");

}