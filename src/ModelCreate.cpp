#include "ModelCreate.h"

#include <iostream> // std::istream in method : file_to_string.

#include <string> // in all methods.
#include <algorithm> // std::find in method : file_to_string.
#include <fstream>
#include <vector> // .push_back() in method : file_to_string.

#include <stdexcept> // std::runtime_error in method : file_to_string.

#include <map> // in methods : kgram_initial_maps & kgram_estimates_map.

// the three logic methods :

// read the file into a std::string, also updates chars with characters obeserved in filename. If the string length < int o, then it throws an exception! 
std::string ModelCreate::file_to_string(std::string filename, int k, std::string errorMsg) {

    // check : file should exist in directory.
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::string errorMsg9 = errorMsg + " - specifically : textfile " + filename + " does not exist in directory.";
        throw std::runtime_error(errorMsg9);
    }
    
    char c;
    std::string text = "";
    
    // reads all characters in the file, file.get(c) == FALSE at the end of the file.
    while (file.get(c)) {
        text += c;

        // searching for c in chars, if not found, add to chars_.
        if (std::find(chars_.begin(), chars_.end(), c) == chars_.end()) {
            chars_.push_back(c);
        }
    }

    // last required error handling.
    if (text.length() <= k) {
        std::string errorMsg10 = errorMsg + " - specifically : length of textfile " + std::to_string(text.length()) + ", is smaller than k (" + std::to_string(k) + ").";
        throw std::runtime_error(errorMsg10);
    }

    return text;
}

// calls method file_to_string, then updates std::map<string, std::map<char, double>> map_ & std::map<string, double> map_freq.
void ModelCreate::kgram_initial_maps(std::string filename, int k, std::string errorMsg) {
    
    // call to read file into a std::string.
    std::string text = file_to_string(filename, k, errorMsg);

    // loop through indexes in the the text to find all (but the last) kgram.
    for (size_t i = 0; i + k < text.length(); ++i) {
        // the kgram starting at index i, and the next character.
        std::string kgram = text.substr(i,k);
        char next_char = text[i+k];

        // update map_freq:
        map_freq[kgram]++;

        // update map_:
        map_[kgram][next_char]++;
    }

    // update map_freq with the last kgram.
    std::string kgram = text.substr(text.length() - k);
    map_freq[kgram]++;

    // having updated map_freq to be the absolute frequency (amount of observations in text), now :
    // update map_freq to be the relative frequency (number of times kgram=w (specific) in text) / (amount of kgrams in the text)
    double total_kgrams = text.length() - k + 1;
    for (auto& [kgram, count] : map_freq) {
        count /= total_kgrams;
    }
}

// updates map_ by process : calculates P(c|w) for all c in chars_, for all w in map_. also updates map_standard_estimates : keys = characters from char_ & values = 1/(chars_.length()).
void ModelCreate::kgram_estimates_map(double p) {

    // update map_standard_estimates.
    for (char c : chars_) {
        map_standard_estimates[c] = 1.0 / chars_.size();
    }

    // iterate over kgrams in map_.
    for (auto& [kgram, kgram_map] : map_) {
        
        // iterate over characters in kgram_map.
        int kgram_sum = 0;
        for (auto& [c, abs_freq] : kgram_map) {
            kgram_sum += abs_freq;
        }

        // a temporary map for updating one kgram's (w) estimates P(c|w).
        std::map<char, double> kgram_c_estimates;

        // iterate over characters in chars_.
        for (char c : chars_) {

            // igen för mig - map_name.find(c) returnerar pekare till var i map_name som c hittades, eller om c ej hittades returnerar .find(c) istället kgram_map.end() [en markör i slutet av mappen].
            // ? om_sant så händer det som står här : om_falskt så händer det som står här.
            // it->second returns value (it->first would return key).
            auto it = kgram_map.find(c);
            double abs_freq = (it != kgram_map.end()) ? it->second : 0.0;

            // updating c's value to P(c|w).
            kgram_c_estimates[c] = ( abs_freq + p ) / ( kgram_sum + p * chars_.size() );
        }

        // update map_.
        map_[kgram] = kgram_c_estimates;
    }
}



// four getter methods, one each for the four private variables.

const std::vector<char>& ModelCreate::get_chars() const {
    return chars_;
}

const std::map<std::string, std::map<char, double>>& ModelCreate::get_map() const {
    return map_;
}

const std::map<std::string, double>& ModelCreate::get_map_freq() const {
    return map_freq;
}

const std::map<char, double>& ModelCreate::get_map_standard_estimates() const {
    return map_standard_estimates;
}
