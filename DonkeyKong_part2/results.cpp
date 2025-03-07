#include <limits>
#include <fstream>

#include "Results.h"

// create a list from results file
Results Results::loadResults(const std::string& filename, bool& is_exist, bool& with_color) {
	Results results; 
	std::ifstream results_file(filename); // open file for reading
	if (!results_file.is_open()) {		  // check open file success
		is_exist = false;
		return results;
	}
	results_file >> with_color;			  // get color mode
	size_t size;
	results_file >> size;				  
	while (!results_file.eof() && size-- != 0) {	
		size_t iteration;
		int result;
		results_file >> iteration >> result;	// get iterarion and result number
		results.addResult(iteration, static_cast<ResultValue>(result));	// add to the list 
	}
	return results;
}

// put in results file the data from the results list and additional information
void Results::saveResults(const std::string& filename, int score, bool with_color) const {
	std::ofstream results_file(filename);		// open file for writing
	results_file << with_color << std::endl;	// put color mode
	results_file << results.size();				// put num of results
	for (const auto& result : results) {		// write results and itreration
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file << std::endl;
	results_file << score;						// write score
	results_file.close();
}

// get next iteration with hit event
size_t Results::getNextBombIteration() const {
	if (!results.empty() && results.front().second == hitBomb) {	// not empty and hit 
		return results.front().first;								// return iteration
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}

