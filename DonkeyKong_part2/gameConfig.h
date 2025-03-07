#pragma once
#include "position.h"
#include "results.h"
#include "steps.h"
#include <iostream>
#include <fstream>
#include <vector>

class Barrel;
class Hero;
class Ghost;
class Board;
class SuperGhost;
class Enemy;

class GameConfig
{
protected:

	long random_seed;											// store the random seed
	void printInstruction() const;								// prints the instructions screen             
	void printExit() const;										// prints the exit screen             
	void printPause() const;                                    // prints the pause screen                     
	void printError(int type_of_error) const;                   // prints an error screen according to the type of loading error
	void pickALevel();											// printd the level picking screen
	bool checkIsWinner(Hero mario) const;						// checks if the hero has reached end point                	
	bool checkIsBadMove(Hero& mario, std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts, bool& game_over, bool isSilent);	// checks if mario was hit
	void resetGame(Hero& mario, std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts);										// resets the game if the hero was hit
	std::vector<std::string> sliceVector(const std::vector<std::string>& inputVector, int startIndex);																	// slice vector to the relevant maps 

public:
	
	void run(bool with_color, std::vector<std::string>& fileNames);												// activates gameplay according to the given color mode and files
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration) const;	// prints unmatching result error
	void initAllGhosts(Board& pboard, std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts) const;	// initializes all kind of ghosts
	void movingIllusionGhosts(std::vector<Ghost>& ghost, std::vector<SuperGhost>& super_ghost) const;			// moving all ghosts in the screen
	void createFilesNames(const std::string& filename, std::string& filename_prefix, std::string& stepsFilename, std::string& resultsFilename) const;	// creates all files names
	void checkGhostCollision(std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts) const;			// checks collision between ghosts and changes direction accordingly
	void clearInputBuffer() const;																				// cleans key buffer

	// -- virtual functions
	virtual bool initGame(const std::string stepsFilename, const std::string resultsFilename, Steps& steps, Results& results, bool& with_color) = 0;		// preparing game files
	virtual bool checkResults(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results, int marioLives) = 0;				// handles "bomb" iteration for results files in load
	virtual bool updateHit(size_t& nextBombIteration, const std::string filename, size_t& iteration, Results& results) = 0;									// updates hit state and results file according to the game
	virtual bool checkMissingHit(size_t& nextBombIteration, const std::string filename, size_t& iteration) = 0;												// checks if there was a hit the didn't happen
	virtual void drawAllCharacters(Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, std::vector<SuperGhost>& super_ghosts) const = 0;	// draws all characters on the screen
	virtual void menu() = 0;																																// presenting the menu options
	virtual void printBoard(bool with_color, Board& board) const = 0;																						// prints the game map
	virtual void printWinner() const = 0;																													// prints the winner screen 
	virtual void printGameOver() const = 0;																													// prints the game over screen

	// getters
	virtual bool getIsSilent() const = 0;	    // gets if the game is on silent mode
	virtual int  getSleepDuration() const = 0;	//  the correct sleep duration according to the mode
	//// gets finish situation in load mode or saves game in save mode
	virtual void getFinish(const std::string filename, size_t& iteration, const std::string resultsFilename, const std::string stepsFilename, Steps& steps, Results& results, int score, bool with_color) = 0;
	//// gets the user input according to the mode
	virtual bool getInput(Board& board, Hero& mario, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, size_t& iteration, bool with_color, Steps& steps) const = 0;
	
	// screen consts
	static constexpr int MAX_WIDTH = 80;
	static constexpr int MAX_HEIGHT = 25;
	static constexpr int ESC = 27;
	static constexpr int NEXT = 110;
	static constexpr int NEW_GAME = 49;
	static constexpr int PICK_A_LEVEL = 53;
	static constexpr int INSTRUCTION = 56;
	static constexpr int EXIT = 57;
	static constexpr int TEN = 10;
	static constexpr int NEW_GAME_WITH_COLORS = 50;
	static constexpr int SCREENS_TOP_MARGIN = 5;
	static constexpr int SCREENS_MIDDLE_WIDTH = 30;

	// Mario consts
	static constexpr int JUMP_H = 2;
	static constexpr int MAX_LIFE = 3;
	static constexpr int MIN_FALL_HEIGHT_MARIO = 5;
	static constexpr int HIT_POINTS = 10;

	// barrel consts
	static constexpr int MIN_FALL_HEIGHT_BARREL = 8;
	static constexpr int EXPLOSION_RADIUS = 2;

	// game loop consts
	static constexpr int SLEEP_DURATION = 100;
	static constexpr int LOAD_SLEEP_DURATION = 35;
	static constexpr int SCREENS_SLEEP_DURATION = 5;
	static constexpr int LOAD_SCREENS_SLEEP_DURATION = 2;
	static constexpr int LOOP_COUNTER = 30;

	enum class errors {
		missing_mario = 1,
		missing_pauline = 2,
		missing_dkong = 3,
		missing_legend = 4,
		no_maps = 5,
	};
	

};

