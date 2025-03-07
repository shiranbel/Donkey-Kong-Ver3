#include "autoGame.h"
#include "barrel.h"
#include "ghost.h"
#include "hero.h"
#include "steps.h"
#include "superGhost.h"

// this function draws characters if were not in silent mode else draws only in current board
void AutoGame::drawAllCharacters(Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, std::vector<SuperGhost>& super_ghosts) const{
	if (!isSilent) {
		mario.draw();

		for (auto& ghost : ghosts)            // draw ghosts
			ghost.draw();

		for (auto& super_ghost : super_ghosts)            // draw ghosts
			super_ghost.draw();

		for (auto& barrel : barrels)          // draw barrels
			barrel.draw();
	}
	else {	
		for (auto& ghost : ghosts)            // draw ghosts
			ghost.drawInCurr();

		for (auto& super_ghost : super_ghosts)            // draw ghosts
			super_ghost.drawInCurr();	// TODO: fix this

		for (auto& barrel : barrels)          // draw barrels
			barrel.drawInCurr();
	}
}

// this function gets the input for the hero's movement from the steps file
bool AutoGame::getInput(Board& board, Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, size_t& iteration, bool with_color, Steps& steps) const {
	if (steps.isNextStepOnIteration(iteration)) {	// checks if the step file is not empty or matches iteration
		char key = steps.popStep();					// get step

		if (key == (char)Hero::keys::attack)		// if it's an attack
			mario.attack(ghosts, barrels);			// attack

		else mario.keyPressed(key);					// for movement
	}
	return true;
}

// this function gets the input for the hero's movement from the steps file
bool AutoGame::updateHit(size_t& nextBombIteration ,const std::string filename, size_t& iteration, Results& results) {
	// check if the result is correct
	if (results.popResult() != std::pair{ iteration, Results::hitBomb }) {
		reportResultError("Results file doesn't match hit bomb event!", filename, iteration);
		unmatching_result_found = true;
		return true;
	}
	nextBombIteration = results.getNextBombIteration();
	return false;
}

// this function checks present the finish state if theres an unmatching result
void AutoGame::getFinish(const std::string filename, size_t& iteration, const std::string resultsFilename, const std::string stepsFilename, Steps& steps, Results& results, int score, bool with_color) {
	if (!unmatching_result_found) {		// if unmatching result has not been found
		if (results.popResult() != std::pair{ iteration, Results::finished }) {		// last result not matching end game
			reportResultError("Results file doesn't match finished event!", filename, iteration);
			unmatching_result_found = true;
		}
		if (results.popResult().second != Results::noResult) {						// last result not matching noResult
			reportResultError("Results file has additional events after finish event!", filename, iteration);	// game kept going
			unmatching_result_found = true;
		}
	}
}

// this function loads the stpes and results file
bool AutoGame::initGame(const std::string stepsFilename, const std::string resultsFilename, Steps& steps, Results& results, bool& with_color) {
	bool is_exist = true;
	steps = Steps::loadSteps(stepsFilename, is_exist); // get steps from file and put in list
	if (!is_exist) {
		std::cout << "        Steps file: " << stepsFilename << " not found, press any key to next screen" << std::endl;
		std::cout << "                                          " << std::endl;
		std::cout << "                                          " << std::endl;
		std::cout << "        		       .--.            .---." << std::endl;
		std::cout << "        		   .---|__|    .-.     |~~~|" << std::endl;
		std::cout << "        		.--|===|--|    |_|     |~~~|--." << std::endl;
		std::cout << "        		|  |===|  |.---!~|  .--|   |--|" << std::endl;
		std::cout << "        		|==|   |  ||===| |--|<<|   |  |" << std::endl;
		std::cout << "        		|==|   |  ||   | |__|  |   |  |" << std::endl;
		std::cout << "        		|  |   |  ||===| |==|  |   |  |" << std::endl;
		std::cout << "        		|  |   |__||   |_|__|  |~~~|__|" << std::endl;
		std::cout << "        		|  |===|--||===|~|--|>>|~~~|--|" << std::endl;
		std::cout << "        		^--^---'--^---^-^--^--^---'--' " << std::endl;
		_getch();
		return true;   // file not exist 
	}
	random_seed = steps.getRandomSeed();			   // get random seed
	results = Results::loadResults(resultsFilename, is_exist, with_color);	// get results from file and put in list
	if (!is_exist) {
		std::cout << "        Results file: " << resultsFilename << " not found, press any key to next screen" << std::endl;
		std::cout << "                                          " << std::endl;
		std::cout << "                                          " << std::endl;
		std::cout << "        		       .--.            .---." << std::endl;
		std::cout << "        		   .---|__|    .-.     |~~~|" << std::endl;
		std::cout << "        		.--|===|--|    |_|     |~~~|--." << std::endl;
		std::cout << "        		|  |===|  |.---!~|  .--|   |--|" << std::endl;
		std::cout << "        		|==|   |  ||===| |--|<<|   |  |" << std::endl;
		std::cout << "        		|==|   |  ||   | |__|  |   |  |" << std::endl;
		std::cout << "        		|  |   |  ||===| |==|  |   |  |" << std::endl;
		std::cout << "        		|  |   |__||   |_|__|  |~~~|__|" << std::endl;
		std::cout << "        		|  |===|--||===|~|--|>>|~~~|--|" << std::endl;
		std::cout << "        		^--^---'--^---^-^--^--^---'--' " << std::endl;
		_getch();
		return true;   // file not exist 
	}
	return false;		// success
}

// this function checks if an action in the game matches the result file
bool AutoGame::checkResults(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results, int marioLives)  {
	if (results.isFinishedBy(iteration, marioLives)) {
		if (marioLives == 1) {
			return false;
		}
		else {
			reportResultError("Results file reached finish while game hadn't!", filename, iteration);
			unmatching_result_found = true;
			return true;

		}
	}
	else {
		nextBombIteration = results.getNextBombIteration();
		return false;
	}
}

// checks if there is a hit in result the didnt happen
bool AutoGame::checkMissingHit(size_t& nextBombIteration, const std::string filename, size_t& iteration)  {
	if (iteration == nextBombIteration && iteration > 0) {
		reportResultError("Results file has a hit bomb event that didn't happen!", filename, iteration);
		unmatching_result_found = true;
		return true;
	}
	return false;
}

// in load mode there's no actual menu so this function calls the run immediately
void AutoGame::menu() {
	ShowConsoleCursor(false);   // hides cursor
	std::vector<std::string> fileNames = {};
	run(false, fileNames);
}

// prints winner screen and ends the program without input
void AutoGame::printWinner() const {
	ShowConsoleCursor(false);		// hides cursor
	system("cls");					// erases the screen

	// the victory screen
	gotoxy(0, SCREENS_TOP_MARGIN);
    std::cout << "	                        == YOU WON!!! ==                         	 " <<std:: endl;
	std::cout << R"(                                  ___________
                                 '._==_==_=_.'
                                 .-\:      /-.
                                | (|:.     |) |
                                 '-|:.     |-'
                                   \::.    /
                                    '::. .'
                                      ) (
                                    _.' '._
                                   `"""""""`)" << std::endl;
	std::cout << "	                                                                     " << std::endl;
	std::cout << "	              \"Oh Mario! You saved me! I LOVE YOU!\"                " << std::endl;
}

// prints game over screen and ends the program without input
void AutoGame::printGameOver() const {
	ShowConsoleCursor(false);		// hides the cursor
	system("cls");					// erases the screen

	// exit screen
	gotoxy(0, SCREENS_TOP_MARGIN);
	std::cout << R"(		  __ _  __ _ _ __ ___   ___    _____   _____ _ __ 
		 / _` |/ _` | '_ ` _ \ / _ \  / _ \ \ / / _ \ '__|
		| (_| | (_| | | | | | |  __/ | (_) \ V /  __/ |   
		 \__, |\__,_|_| |_| |_|\___|  \___/ \_/ \___|_|   
		 |___/           
)" << std::endl;
	std::cout << "                       Don't give up Mario!! Save the princess                  " <<std:: endl;

}

