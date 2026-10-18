#include "ModelTextGenerator.h"

#include <string>
#include <vector>
#include <map>
#include <random>

// initializes ModelTextGenerator : sets private model variable as the input_model.
ModelTextGenerator::ModelTextGenerator(const ModelCreate& input_model) : model(input_model) {  
}

// estimates / relative frequencies (both double's) can be called weights
// this function can take both map's with the form <char, freq> & <std::string, double> 
// and is named with 'weighted'.
// helper function for method : text_generator.
template <typename T> 
T choose_random_weighted(const std::map<T, double>& weight_map, std::mt19937& gen) {
    
    // declare vectors and splitting up a map's keys & values into.
    std::vector<T> items;
    std::vector<double> weights;
    for (const auto& [item, weight] : weight_map) {
        items.push_back(item);
        weights.push_back(weight);
    }

    // creates a random-function that takes weights/absolute frequencies.
    std::discrete_distribution<int> distribution(weights.begin(), weights.end());
    // returns the chosen kgram/character.
    return items[distribution(gen)];
}

std::string ModelTextGenerator::text_generator(int k, int o, int p) {

    std::random_device rd;
    std::mt19937 gen(rd());

    // randomly (weighted) choose a kgram from map_freq_.
    std::string chosen_kgran  = choose_random_weighted(model.get_map_freq(), gen);

    // declare the running-updating result_text, that is to be returned at algorithm end.
    std::string result_text = chosen_kgran;

    // running until the result_text has the desired length (or if )
    while (result_text.length() < o) {

        // current_kgram is always the last k characters in result_text.
        std::string current_kgram = result_text.substr(result_text.length() - k);

        // a pointer to chose_kgram in map_ ( if not found, map_.end() ).
        auto it = model.get_map().find(current_kgram);

        char next_char;

        // handling different cases ( chosen kgram not in model.get_map(), in model.get_map() ) and subcases (p = 0, p > 0).
        if  (it == model.get_map().end()) {
            // chosen_kgram not in model.get_map().
            if (p == 0) {
                // when p = 0, the model can miss kgram estimates(weights), because kgram was never observed in training data, then we don't use model.get_map_standard_estimates().
                return result_text;
            } else {
                // when p > 0, the model cannot miss kgram estimates, then we do use model.get_map_standard_estimates().
                next_char = choose_random_weighted(model.get_map_standard_estimates(), gen);
            }
        } else {
            // it->second is model.get_map()'s value std:.map<char, double>.
            next_char = choose_random_weighted(it->second, gen);
        }
        // updating the resulting text : each loop.
        result_text += next_char;
    }
    return result_text;
}
