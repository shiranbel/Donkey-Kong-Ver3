#include <fstream>
#include <iostream>

#include "Steps.h"

// create a list from steps file
Steps Steps::loadSteps(const std::string& filename, bool &is_exist) {
	Steps steps;
	std::ifstream steps_file(filename);	// open file for reading
	if (!steps_file.is_open()) {		// check open file success
		is_exist = false;
		return steps;
	}
	
	steps_file >> steps.randomSeed;		// get random seed
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;	// get iteration and key
		steps.addStep(iteration, step);		// add to the list
	}
	steps_file.close();
	return steps;
}

// put in steps file the data from the steps list
void Steps::saveSteps(const std::string& filename) const {
	std::ofstream steps_file(filename);					// open file for writing
	steps_file << randomSeed << '\n' << steps.size();	// put num of steps
	for (const auto& step : steps) {					// write steps and iteration
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}
