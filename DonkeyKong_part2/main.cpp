#include "gameConfig.h"
#include "autoGame.h"
#include "manualGame.h"
#include <Windows.h>
#include <iostream>
					

int main( int argc, char** argv) {

	// figure the game mode fron main argumanets
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";

	GameConfig* game = nullptr;

	if (isLoad) {
		game = new AutoGame(isSilent);
		game->menu();
	}
	else if (argc >= 1) { // save mode
		game = new ManualGame(isSave);
		game->menu();
	}

	// Delete the allocated memory when done
	delete game;
}