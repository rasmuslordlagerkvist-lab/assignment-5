// class ModelCreate

// Private (variables): 
// std::vector<char> chars_.
// std::map<string, std::map<char, double>> map_. 
// std::map<string, double> map_freq.
// std::map<char, double> map_standard_estimates.

// Public (functions): 
// file_to_string(file, k) - reads the file into a string that it returns, unless the string length is less than k, then it throws an exception and stops ModelCreate's process!
//                         - also updates chars_ with the observed characters in the training text.
// kgram_initial_maps(file, k) - calls file_to_string, then creates kgram_map and kgram_map_freq.map_standard_estimates
// kgram_map_estimates(p = 0) - calculates P(c|w) for all c, for all w=keys in map_. also updates map_standard_estimates, where keys are characters from chosen alphabeth and values are 1/(amount of characters in the alphabet).

// maybe splitting up ^^ intosmaller helper functions. Not sure on this until I actually code it.



class ModelCreate {

    private:
        std::vector<char> chars_;
        std::map<string, std::map<char, double>> map_;
        std::map<string, double> map_freq;
        std::map<char, double> map_standard_estimates;

    public:

        // read the file into a std::string, also updates chars with characters obeserved in filename. If the string length < int o, then it throws an exception! 
        std::string file_to_string(std::istream& file, int k, std::string errorMsg);

        // calls method file_to_string, then updates map_ & map_freq.
        void kgram_initial_maps(std::istream& file, int k, std::string errorMsg);

        // updates map_ by process : calculates P(c|w) for all c in chars_, for all w in map_. also updates map_standard_estimates : keys = characters from char_ & values = 1/(chars_.length()).
        void kgram_estimates_map(double p = 0);
}



