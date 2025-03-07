#pragma once

#include <list>

class Steps {
	long randomSeed = 0;
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
	// create a list from steps file
	static Steps loadSteps(const std::string& filename, bool& is_exist);	

	// put in steps file the data from the steps list
	void saveSteps(const std::string& filename) const;		

	// set the random seed of the level
	void setRandomSeed(long seed) {randomSeed = seed;}		

	// add a step to the step list
	void addStep(size_t iteration, char step) {	steps.push_back({ iteration, step });}	

	// checks if next itr is not empty and equals to current itr
	bool isNextStepOnIteration(size_t iteration) const {return !steps.empty() && steps.front().first == iteration;} 

	// pop a step from the steps list
	char popStep() {														
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}

	// returns the random seed
	long getRandomSeed() const {return randomSeed;}							
};
