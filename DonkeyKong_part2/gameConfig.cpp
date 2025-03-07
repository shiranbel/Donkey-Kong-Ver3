#include <conio.h>
#include "gameConfig.h"
#include "board.h"
#include "hero.h"
#include "utils.h"
#include "ghost.h"
#include "results.h"
#include "steps.h"
#include "superGhost.h"
#include "manualGame.h"
#include "autoGame.h"
#include "barrel.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;

// this function slice vector to the rellevant maps by start index
std::vector<std::string> GameConfig::sliceVector(const std::vector<std::string>& inputVector, int startIndex) {
	// if the index is out of bounds, return an empty vector
	if (startIndex >= inputVector.size()) {
		return {};
	}
	// use vector's range constructor to create a new vector
	return std::vector<std::string>(inputVector.begin() + startIndex, inputVector.end());
}

// this function prints all the files in the vector, slices the vector according to the user's choice,
// and calls run function to start the game with the chosen map
void GameConfig::pickALevel() {
	std::vector<std::string> fileNames;
	getAllBoardFileNames(fileNames);            // get all files name into filenames vector
	
	int index = 1;
	gotoxy(SCREENS_MIDDLE_WIDTH, SCREENS_TOP_MARGIN);
	std::cout << "Pick your level:" << endl;
	gotoxy(SCREENS_MIDDLE_WIDTH, SCREENS_TOP_MARGIN + index);
	index++;
	std::cout << "Press any other key for level 1 :" << endl;
	// print files name and press key
	for (const auto& filename : fileNames) {
		gotoxy(SCREENS_MIDDLE_WIDTH, SCREENS_TOP_MARGIN + index);
		cout << "(" << index-1 << ") " << filename << endl;
		index++;
	}

	char choice = _getch();       // user's input
	index = choice - '0' - 1;     // convert to int

	fileNames = sliceVector(fileNames, index);   
	system("cls");
	gotoxy(TEN, SCREENS_TOP_MARGIN);
	// print a colors game option 
	std::cout << "Do you want to play with colors?  Press:   (1) Yes    (2) No" << endl;

	char color_choice = _getch();  // user's input
	// send the rellevant color 
	if(color_choice == '1')
		run(true, fileNames);
	else
		run(false, fileNames);
}
 
// this function print the type of error by getting a int code error
void GameConfig::printError(int type_of_error) const{
	ShowConsoleCursor(false);					// hides th e cursor

	switch (type_of_error) {
	case (int)errors::no_maps:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                         We didn't find your level Mario                     " << endl;
		cout << "                       Press ESC to return to the main menu.                 " << endl;
		cout << "                                                                             " << endl;
		cout << R"(                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    ~ ~ ~ ~ ~ ~ ~ ~ ^ ^ ^ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
                    ~  Princess     ^     ^     =======        ~
                    ~   ^^^      ^  ~~~  ^   H         T T T   ~
                    ~   ^ ^      ^  ~~~      H<<<        T T   ~
                    ~   ^ ^      ^           H     #########   ~
                    ~     P      ~~~         H     # Score #   ~
                    ~     ~~~    ~~~  Dkong  H     #  100  #   ~
                    ~     ~~~    ~~~               #########   ~
                    ~     ~~~    ~~~    O                  O   ~
                    ~  Mario    #####   O O      X         O O ~
                    ~ ~ ~ ~ ~ ~ #####   O O O    X X X     O O ~
                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)" << endl;
		break;
	case (int)errors::missing_mario:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                               Missing Mario                                 " << endl;
		cout << "                  How can you save a princess without a hero?                " << endl;
		cout << "                       Press ESC to go to the next level.                    " << endl;
		cout << "                                                                             " << endl;
		cout << R"(
                          _____________________________   
                         /        _____________        \  
                         | == .  |             |     o |  
                         |   _   |    Where    |    B  |  
                         |  / \  |             | A   O |  
                         | | O | |      is     |  O    |  
                         |  \_/  |             |       |  
                         |       |    Mario?   | . . . |  
                         |  :::  |             | . . . |  
                         |  :::  |_____________| . . . |  
                         |           S N K             |  
                         \_____________________________/
)" << endl;		       

		break;
	case (int)errors::missing_pauline:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                               Missing Pauline                               " << endl;
		cout << "                         Who do you want to save then?                       " << endl;
		cout << "                       Press ESC to go to the next level.                    " << endl;
		cout << "                                                                             " << endl;
		cout << R"(                                  o  o   o  o
                                  |\/ \^/ \/|
                                  |,-------.|
                                ,-.(|)   (|),-.
                                \_*._ ' '_.* _/
                                 /`-.`--' .-'\ 
                            ,--./    `---'    \,--.
                            \   |(  )     (  )|   /
                             \  | ||       || |  /
                              \ | /|\     /|\ | /
                              /  \-._     _,-/  \
                             //| \\  `---'  // |\\
                            /,-.,-.\       /,-.,-.\ 
                           o   o   o      o   o    o)" << endl;
		break;
	case (int)errors::missing_dkong:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << "                               Missing Donkey Kong                           " << endl;
		cout << "                No enemies? playing without enemies is very boring           " << endl;
		cout << "                       Press ESC to go to the next level.                    " << endl;
		cout << "                                                                             " << endl;
		cout << R"(                     //\
                     V  \
                      \  \_
                       \,'.`-.  Donkey Kong took a lunch break :)
                        |\ `. `.       
                        ( \  `. `-.                        _,.-:\
                         \ \   `.  `-._             __..--' ,-';/
                          \ `.   `-.   `-..___..---'   _.--' ,'/ 
                           `. `.    `-._        __..--'    ,' /  
                             `. `-_     ``--..''       _.-' ,'   
                               `-_ `-.___        __,--'   ,'     
                                  `-.__  `----"""    __.-'       
                                       `--..____..--'            
)" << endl;
		break;
	case (int)errors::missing_legend:				
		system("cls");
		gotoxy(0, SCREENS_TOP_MARGIN);
		cout << R"(
            ____________________              Missing legend
           /                    \        Are we still in matala 1? 
           |     In case of     |    Press ESC to go to the next level. 
           |     Frustration    |
           \____________________/
                    !  !
                    !  !
                    L_ !
                   / _)!
                  / /__L
            _____/ (____)
                   (____)
            _____  (____)
                 \_(____)
                    !  !
                    !  !
                    \__
)" << endl;
		break;
	default:
		break;
	}

	
	char ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the exit screen
void GameConfig::printExit() const {
	ShowConsoleCursor(false);					// hides th e cursor

	// exit screen
	gotoxy(0, SCREENS_TOP_MARGIN);
	cout << "         Farewell, Mario. The princess was waiting for you to save her, " << endl;
	cout << "                         but perhaps another time...                    " << endl;
	std::cout << R"( 
                   _____                 _ ____             
                  / ____|               | |  _ \            
                 | |  __  ___   ___   __| | |_) |_   _  ___ 
                 | | |_ |/ _ \ / _ \ / _` |  _ <| | | |/ _ \
                 | |__| | (_) | (_) | (_| | |_) | |_| |  __/
                  \_____|\___/ \___/ \__,_|____/ \__, |\___|
                                                  __/ |     
                                                 |___/     
)" << std::endl;
}

// this function prints the instructions screen
void GameConfig::printInstruction() const {
	ShowConsoleCursor(false);		// hides the cursor

	// instructions screen
	gotoxy(0, SCREENS_TOP_MARGIN - 1);
	char ch;
	//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
	cout << "                             === INSTRUCTIONS ===                               " << endl;
	cout << "                    Use the following keys to play the game:                    " << endl;
	cout << "                        - W/w : Up / Jump                                       " << endl;
	cout << "                        - X/x : Down                                            " << endl;
	cout << "                        - A/a : Left                                            " << endl;
	cout << "                        - D/d : Right                                           " << endl;
	cout << "                        - S/s : Stay                                            " << endl;
	cout << "                        - P/p : Attack (when hammer mode is on)                 " << endl;
	cout << "                        - N/n : Skip the level                                  " << endl;
	cout << "                     Press ESC to return to the main menu.                      " << endl;
	cout << "				  _._______" << endl;
	cout << "				 | _______ |" << endl;
	cout << "				 ||,-----.||" << endl;
	cout << "				 |||     |||" << endl;
	cout << "				 |||_____|||" << endl;
	cout << "				 |`-------'|" << endl;
	cout << "				 | +     O |" << endl;
	cout << "				 |      O  |" << endl;
	cout << "				 | / /  ##,\"" << endl;
	cout << "				  `------\"" << endl;


	// returns to menu when pressing ESC
	ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the pausing screen
void GameConfig::printPause() const {
	ShowConsoleCursor(false);	// hides the cursor
	system("cls");				// eracing the screen
	// visuals
	gotoxy(0, SCREENS_TOP_MARGIN);
	cout << R"(
		.-------.    ____      ___    _    .-'''-.     .-''-.   
		\  _(`)_ \ .'  __ `. .'   |  | |  / _     \  .'_ _   \  
		| (_ o._)|/   '  \  \|   .'  | | (`' )/`--' / ( ` )   ' 
		|  (_,_) /|___|  /  |.'  '_  | |(_ o _).   . (_ o _)  | 
		|   '-.-'    _.-`   |'   ( \.-.| (_,_). '. |  (_,_)___| 
		|   |     .'   _    |' (`. _` /|.---.  \  :'  \   .---. 
		|   |     |  _( )_  || (_ (_) _)\    `-'  | \  `-'    / 
		/   )     \ (_ o _) / \ /  . \ / \       /   \       /  
		`---'      '.(_,_).'   ``-'`-''   `-...-'     `'-..-'   
		    )" << endl;
	cout << "\n";
	cout << "                                Press ESC to resume";
}

// this function checks if the hero is at the same position of the princess
bool GameConfig::checkIsWinner(Hero mario) const {
	return (mario.getBoard()->getCharFromOriginal(mario.getPosition().getX(), mario.getPosition().getY()) == (char)Board::characters::pauline);
}

// this function resets the game when the hero is damaged by resetting the hero and the barrels
void GameConfig::resetGame(Hero& mario, std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts){
	mario.resetMario();						// resets the hero
	mario.getBoard()->returnHammer();
	mario.getBoard()->updateHammer(mario.getWithHammer());

	for (auto& barrel : barrels)			// erase all barrels from screen
		barrel.erase();

	mario.changelives();					// decreace the hero's remaining lives
	mario.getBoard()->resetNumOfGhosts();
	mario.getBoard()->resetNumOfSuperGhosts();

	for (auto& ghost:ghosts)				// erase all ghosts from screen
		ghost.erase();

	for (auto& super_ghost : super_ghosts)	// erase all super ghosts from screen
		super_ghost.erase();

	barrels.clear();						// delete all enemies from their vector
	ghosts.clear();
	super_ghosts.clear();

	for (int i = 0; i < mario.getBoard()->getVectorGhost().size(); i++) {
		ghosts.emplace_back(mario.getBoard());
	}
	for (int i = 0; i < mario.getBoard()->getVectorSuperGhost().size(); i++) {
		super_ghosts.emplace_back(mario.getBoard());
	}	
}

// this function prints a result error according to the given meesage and present the iteration error
void GameConfig::reportResultError(const std::string& message, const std::string& filename, size_t iteration) const{
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	//std::cout << "Iteration: " << iteration << '\n';
	//std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	std::cout << R"(
                                                            || __   ||
       Iteration: )" << iteration << R"(                                       ||=\_`\=||
       Press any key to continue to next screens (if any)   ||  | | :-"""-.
                                                            ||==| \/-=-.   \
                                                            ||  |(_|o o/   |_
                                                            ||   \/ "  \   ,_)
                                                            ||====\ ^  /__/
                                                            ||     ;--'  `-.
                                                            ||    /      .  \
                                                            ||===;        \  \
                                                            ||   |   o     | |
                                                            | .-\ '     _/_/
                                                            |:'  _;.    (_  \
                                                            /  .'  `;\   \\_/
                                                           |_ /     |||  |\\
                                                          /  _)=====|||  | ||
                                                         /  /|      ||/  / //
                                                         \_/||      ( `-/ ||
                                                            ||======/  /  \\ .-.
                                                            ||      \_/    \'-'/
                                                            ||      ||      `"`
   )" << std::endl;
	_getch();		// pres any key to continue
}

// checks if mario was hit and resets or finishes the game if mario was hit
bool GameConfig::checkIsBadMove(Hero& mario, std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts, bool& game_over, bool isSilent) {
	if (mario.getIsFalling() || mario.isCollision()) {   // checks if Mario has fallen and reset the game if necessary 
		mario.setScore(0);								 // reset score
		resetGame(mario, barrels, ghosts, super_ghosts); // reset game elements
		if (mario.getLife() == 0) {
			if (!isSilent) {
				printGameOver();						 // print game over
			}
			else {
				system("cls");
				cout << "Results file loaded successfully";
			}
			
			game_over = true;							 // finish the game
		}
		else game_over = false;							 // only reset but continue
		return true;	
	}
	return false;
}

// this function flushes any remaining characters in the buffer
void GameConfig::clearInputBuffer() const {
	// Flush any remaining characters in the buffer
	while (_kbhit()) {
		_getch(); // Read and discard any extra characters
	}
}

// this function runs the game loop and handles the game's actions and effects
void GameConfig::run(bool with_color, std::vector<std::string>& fileNames)  {
	ShowConsoleCursor(false);				                 // hides cursor
	if(fileNames.empty())					                 // if it came without levels get from directory
		getAllBoardFileNames(fileNames);                     // get files names
	if (fileNames.empty()) {                                 // if there are no files in directory
		system("cls");
		printError((int)errors::no_maps);  
		return;
	}

	std::vector<Ghost> ghosts;
	std::vector<SuperGhost> super_ghosts;
	Hero mario; 
	bool isSilent = getIsSilent();

	for (const auto& filename : fileNames) {	             // levels loop
		system("cls");	
		std::vector<Barrel> barrels;						 // initializes max barrels vector
		Board board(with_color, filename, isSilent);		 // init board
		Steps steps;										 // init steps list	
		Results results;									 // init reults list
		std::string filename_prefix, stepsFilename, resultsFilename; // create file names
		createFilesNames(filename, filename_prefix, stepsFilename, resultsFilename);
		
		if (initGame(stepsFilename, resultsFilename, steps, results, with_color)) continue;	 // prepare level if no result of step file - next
		srand(random_seed);									 // get random seed
		size_t iteration = 0;								 
															 
		int error_type = board.checkAllCharacters();		 // checks if all the important characters has been loaded
		if (error_type) {
			system("cls");
			printError(error_type);
			continue;
		}							 
															 
		int game_loop_counter = 0;							 // used to measure the time of the barrels' exit
		printBoard(with_color, board);						 // prints the board in the given color mode 	
		mario.setBoard(&board);								 // set mario's board
															 
		initAllGhosts(board, ghosts, super_ghosts);			 // initialize all ghosts
															 
		for (; !checkIsWinner(mario); ++iteration) {		 // game loop
			size_t nextBombIteration = 0;
			if (checkResults(nextBombIteration, filename, iteration, results, mario.getLife())) break;	// check results matching in load, if false next level

			board.updateScore(mario.getScore());	         // update mario's score
			
			bool game_over = false;
			if(checkIsBadMove(mario, barrels, ghosts, super_ghosts, game_over, isSilent))	// if mario was hit update hit file
				 if (updateHit(nextBombIteration, filename, iteration, results)) break;		// if hit unmatched result file in load - next level
			if (game_over) {						         // if mario got 3 hits finish game
				getFinish(filename, iteration, resultsFilename, stepsFilename, steps, results, mario.getScore(), with_color);	// update finish in result file
				return;
			}

			if (game_loop_counter == 0 )                     // create barrels
				barrels.emplace_back(&board);
			
			drawAllCharacters(mario, ghosts, barrels, super_ghosts); // draw all chacters to the screen
			checkGhostCollision(ghosts, super_ghosts);		 // checks ghosts collision

			if (checkIsBadMove(mario, barrels, ghosts, super_ghosts, game_over, isSilent))	// if mario was hit update hit file
				if (updateHit(nextBombIteration, filename, iteration, results)) break;		// if hit unmatched result file in load - next level
			if (game_over) {	                             // if mario got 3 hits finish game
				getFinish(filename, iteration, resultsFilename, stepsFilename, steps, results, mario.getScore(), with_color);	// update finish in result file
				return;
			}

			if (mario.getJumpCount() > 0)                    // fix jump counter
				mario.handleJump();

			if (!getInput(board, mario, ghosts, barrels, iteration, with_color, steps)) break;
			
			Sleep(getSleepDuration());			             // control speed of movement according to the game mode
												             
			mario.erase();                                   // illusion of Mario's movement
			mario.move();                                    // change position
			
			if (checkIsBadMove(mario, barrels, ghosts, super_ghosts, game_over, isSilent))	// if mario was hit update hit file
				if (updateHit(nextBombIteration, filename, iteration, results)) break;		// if hit unmatched result file in load - next level
			if (game_over) {	                             // if mario got 3 hits finish game
				getFinish(filename, iteration, resultsFilename, stepsFilename, steps, results, mario.getScore(), with_color); // update finish in result file
				return;
			}

			movingIllusionGhosts(ghosts, super_ghosts);	     // handle all ghosts movement on screen

			int index = 0;
			for(auto& barrel : barrels) {
				barrel.erase();                              // erases ghosts
				barrel.move();                               // illusion of ghost's movement
				if (barrel.getIsOnBorder())                  // check if barrel collides with border
					barrels.erase(barrels.begin() + index);  // delete from vector         
				if (barrel.getIsHit()) {                     // check if barrel explodes
					barrel.drawExplode();                    // draw all the relevant collision points of the barrel's explosion in current map
					if (checkIsBadMove(mario, barrels, ghosts, super_ghosts, game_over, isSilent))	// if mario was hit update hit file
						if (updateHit(nextBombIteration, filename, iteration, results)) break;		// if hit unmatched result file in load - next level
					if (game_over) {					     // if mario got 3 hits finish game
						getFinish(filename, iteration, resultsFilename, stepsFilename, steps, results, mario.getScore(), with_color);	// update finish in result file
						return;
					}
					
					barrel.eraseExplode();                   // erase all collision points of the barrel's explosion from current map
					barrels.erase(barrels.begin() + index);  // delete barrel from vector
				}
				index++;
			}
			game_loop_counter++;                                            // game loop counter  
			if (game_loop_counter > LOOP_COUNTER) game_loop_counter = 0;	// for barrel creation handle

			if (checkMissingHit(nextBombIteration, filename, iteration)) break;		// check if there was a hit that didn't happen
		} // end of game loop
		getFinish(filename, iteration, resultsFilename, stepsFilename, steps, results, mario.getScore(), with_color);	// check finish in results file
		iteration = 0;
	}	// end of game
	if (!isSilent) {
		clearInputBuffer();
		printWinner();
	}
	else system("cls");
}

// this function initializes all kind of ghosts at the beggining of the game
void GameConfig::initAllGhosts(Board& pboard, std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts) const {
	ghosts.clear();											   // delete from vector
	for (int i = 0; i < pboard.getVectorGhost().size(); i++)   // create all ghosts with specific position into vector
		ghosts.emplace_back(&pboard);	

	super_ghosts.clear();											// delete from vector
	for (int i = 0; i < pboard.getVectorSuperGhost().size(); i++)   // create all ghosts with specific position into vector
		super_ghosts.emplace_back(&pboard);
}

//  presents the movement of all ghosts in the screen
void GameConfig::movingIllusionGhosts(std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts) const {
	for (auto& ghost : ghosts) // erases ghosts from screen
		ghost.erase();

	for (auto& super_ghost : super_ghosts) // erases super ghosts from screen
		super_ghost.erase();

	for (auto& ghost : ghosts)
		ghost.move(); // illusion of ghost's movement

	for (auto& super_ghost : super_ghosts)
		super_ghost.move(); // illusion of ghost's movement
}

// create the result, steps file names template 
void GameConfig::createFilesNames(const std::string& filename, std::string& filename_prefix, std::string& stepsFilename, std::string& resultsFilename) const {
	filename_prefix = filename.substr(0, filename.find_last_of('.'));
	stepsFilename = filename_prefix + ".steps";
	resultsFilename = filename_prefix + ".result";
}

// this function checks if there is a collision between ghosts and chenges thier direction
void GameConfig::checkGhostCollision(std::vector<Ghost>& ghosts, std::vector<SuperGhost>& super_ghosts) const {
	for (auto& ghost : ghosts) {
		ghost.checkIsCollision();
	}
	for (auto& superGhost : super_ghosts) {
		superGhost.checkIsCollision();
	}
}