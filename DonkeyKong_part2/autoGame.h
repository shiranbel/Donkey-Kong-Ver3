#pragma once
#include "gameConfig.h"
#include <iostream>
#include <conio.h>
#include "board.h"

class AutoGame :public GameConfig
{
	bool isSilent = false;
	bool unmatching_result_found = false;
public:

	// ctor
	AutoGame(bool silent) : isSilent(silent) {}
	
	// this function loads the stpes and results file
	bool initGame(const std::string stepsFilename, const std::string resultsFilename, Steps& steps, Results& results, bool& with_color) override;
	
	// this function check if an action in the game matches the result file
	bool checkResults(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results, int marioLives) override;
	
	// gets the input for the hero's movement from the steps file
	bool getInput(Board& board, Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, size_t& iteration, bool with_color, Steps& steps) const override;
	
	// checks if there was a hit in game and not in results// checks if there was a hit in game and not in results
	bool updateHit(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results) override;
	
	// checks if there is a hit in result the didnt happen
	bool checkMissingHit(size_t& nextBombIteration, const std::string filename, size_t& iteration) override;
	
	// returns the isSilent mode
	bool getIsSilent() const override { return isSilent; }
	
	// draws characters if were not in silent mode else draws only in current board
	void drawAllCharacters(Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, std::vector<SuperGhost>& super_ghosts) const override;
	
	// this function checks present the finish state if theres an unmatching result
	void getFinish(const std::string filename, size_t& iteration, const std::string resultsFilename, const std::string stepsFilename, Steps& steps, Results& results, int score, bool with_color)  override;
	
	// in load mode there's no actual menu so this function calls the run immediately
	void menu() override;
	
	// in load mode this function prints the board only if we are not in silent mode
	void printBoard(bool with_color, Board& board) const override { if(!isSilent) board.print(with_color, LOAD_SCREENS_SLEEP_DURATION); }
	
	// prints winner screen and ends the program without input
	void printWinner() const override;
	
	// prints game over screen and ends the program without input
	void printGameOver() const override;
	
	// gets sleep duration according to silent mode
	int  getSleepDuration() const override {
		if (isSilent)
			return 0;
		return LOAD_SLEEP_DURATION;
	}
};


