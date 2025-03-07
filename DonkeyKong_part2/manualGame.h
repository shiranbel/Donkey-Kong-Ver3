#pragma once
#include "gameConfig.h"
#include "board.h"
#include <filesystem>

class ManualGame : public GameConfig
{
	bool isSave = false;
public:
	// ctor
	ManualGame(bool save) : isSave(save) {}

	// in manual mode there is no silent mode so return false to not to break
	bool getIsSilent() const override { return false; }

	// this function initializes the random seed if we are in save mode
	bool initGame(const std::string stepsFilename, const std::string resultsFilename, Steps& steps, Results& results, bool& with_color) override {
		if (isSave) {
			random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
			steps.setRandomSeed(random_seed);
		}
		return false;	// return false to not to break
	}

	// in manual mode there's no result file to check so return false to not to break
	bool checkResults(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results, int marioLives) override { return false; }
	
	// in manual mode we get the input from the user so this function sends the input to mario's movement
	bool getInput(Board& board, Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, size_t& iteration, bool with_color, Steps& steps) const override;
	
	// this function updates the results file with hit events in save mode
	bool updateHit(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results) override;
	
	// in manual mode there's no result file for comparision so return false to not to break
	bool checkMissingHit(size_t& nextBombIteration, const std::string filename, size_t& iteration) override { return false; }
	
	// in save mode mark finish in result file and save steps and results file with additional given data
	void getFinish(const std::string filename, size_t& iteration, const std::string resultsFilename, const std::string stepsFilename, Steps& steps, Results& results, int score, bool with_color) override {
		if (isSave) {
			results.addResult(iteration, Results::finished);
			steps.saveSteps(stepsFilename);
			results.saveResults(resultsFilename, score, with_color);
		}
	}
	
	// prints the menu screen as in usual game
	void menu() override;
	
	// calls for printing the board according to color selection 
	void printBoard(bool with_color, Board& board) const override  { board.print(with_color, SCREENS_SLEEP_DURATION); }
	
	// this function prints the winning screen
	void printWinner() const override; 
	
	// this function prints the game over screen
	void printGameOver() const override;
	
	// draws all characters to the screen and in current map
	void drawAllCharacters(Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, std::vector<SuperGhost>& super_ghosts) const override;
	
	// get sleep duration in maunal mode
	int  getSleepDuration() const override { return SLEEP_DURATION; }

};


	

