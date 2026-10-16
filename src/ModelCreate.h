// class ModelCreate

// Private (variables): 
// std::map<string, std::map<string, int>> map_, 
// std::map<string, double> map_freq, 
// std::map<string, double> map_standard_estimate - 

// Public (functions): 
// file_to_string(file, o) - reads the file into a string that it returns, unless the string length is less than o, then it throws an exception and stops ModelCreate's process!
// kgram_initial_maps(file, k, o) - calls file_to_string, then creates kgram_map and kgram_map_freq.
// kgram_map_estimates() - calculates P(c|w) for all c, for all w=keys in map_. also updates map_standard_estimate, where keys are characters from chosen alphabeth and values are 1/(amount of characters in the alphabet).

// maybe splitting up ^^ intosmaller helper functions. Not sure on this until I actually code it.
