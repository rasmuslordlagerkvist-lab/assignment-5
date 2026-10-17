#include "ModelTextGenerator.h"

#include <string>
#include <vector>
#include <map>
#include <random>


// initializes ModelTextGenerator : sets private model variable as the input_model.
ModelTextGenerator(const ModelCreate& input_model) : model(input_model) {  
}

std::string text_generator(int k, int o, int p) {

    // choose first kgram (w) based on map_freq_.
    std::vector<std::string> kgrams;
    std::vector<double> rel_freqs;

    for (auto& [kgram, rel_freq] : model.get_map_freq()) {
        kgrams.push_back(kgram);
        rel_freqs.push_back(rel_freq);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<int> distribution(rel_freqs.begin(), rel_freqs.end());
    int chosen_kgram_index = distribution(gen);
    std::string chosen_kgram = kgrams[chosen_kgram_index];

    // declare the running-updating result_text, that is to be returned at algorithm end.
    std::string result_text = chosen_kgram;
    
    // running until the result_text has the desired length (or if )
    while (result_text.length() < o) {

        // current_kgram is always the last k characters in result_text.
        std::string current_kgram = result_text.substr(result_text.length() - k);

        auto it = model.get_map().find(chosen_kgram);

        std::vector<char> chars;
        std::vector<double> estimates;
        
        // updating chars & estimates : depending on whether map_[chosen_kgram] exists and wheter p = 0 or p > 0.
        if (it == model.get_map().end()) {
            // chosen_kgram not in map_.
            if (p == 0) {
                // when p = 0, the model can miss kgram estimates (because kgram was never observed in training data), and then we don't use map_standard_estimates.
                return result_text;
            } else {
                // when p > 0, the model cannot miss kgram estimates, thus we just use map_standard_estimates.
                for (const auto& [c, estimate] : model.get_map_standard_estimates()) {
                    chars.push_back(c);
                    estimates.push_back(estimate);
                }
            }
        } else {
            // it->second returns value (it->first would return key) .
            for (const auto& [c, estimate] : it->second) {
                chars.push_back(c);
                estimates.push_back(estimate);
            }
        }
        
        std::discrete_distribution<int> char_distribution(estimates.begin(), estimates.end());
        int chosen_char_index = char_distribution(gen);
        char next_char = chars[chosen_char_index];

        result_text += next_char;
    }

    return result_text;
}
