#pragma once

#include <list>
#include <string>

class Results {
public:
	enum ResultValue { hitBomb, finished, noResult };	// hitBomb <=> mario was hit by an enemy
private:
	std::list<std::pair<size_t, ResultValue>> results;  // pair: iteration, result
public:
	// create a list from results file
	static Results loadResults(const std::string& filename, bool& is_exist, bool& with_color);	

	// put in results file the data from the results list and additional information
	void saveResults(const std::string& filename, int score, bool with_color) const;	

	// add a result to the result list
	void addResult(size_t iteration, ResultValue result) { results.push_back({ iteration, result }); }  

	// return if the result list is empty or last iteration is less tham curr itr
	bool isFinishedBy(size_t iteration, int marioLives) const {return results.empty() || (results.back().first <= iteration);}	

	// get next iteration with hit event
	size_t getNextBombIteration() const;	

	// pop a result from result list
	std::pair<size_t, ResultValue> popResult() {												      
		if (results.empty()) return { 0, Results::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}		
};
