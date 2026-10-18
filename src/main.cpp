#include "ModelCreate.h"
#include "ModelTextGenerator.h"

int main(int argc, char* argv[]) {

    try {
        // I think this is very useful! args 
        std::vector<std::string> args(argv, argv + argc);

        // part of most error messages : instructions on desired input. - specific error found added in boolean checks.
        std::string errorMsg = std::string("Usage: ") + args[0] + " -a p k textfile o\n" +
                               "p a real non-negative number, k a positive integer, o >= k a positive integer.\n" +
                               "-a and p come as an optional pair of input parameters.\n";
        
        // check : four or more input parameters.
        if (args.size() < 4) {
            std::string errorMsg1 = errorMsg + " - specifically : there were to few input parameters.";
            throw std::invalid_argument(errorMsg1);
        }

        // check : input should be 'args[0] k textfile o' or 'args[0] -a p k textfile o', (4 or 6 input parameters).
        if (args.size() != 4 && args.size() != 6) {
            std::string errorMsg2 = errorMsg + " - specifically : there was " + std::to_string(args.size()) + " input parameters.";
            throw std::invalid_argument(errorMsg2);
        }

        // check : inputs 'k' and 'o' should be positive integers and o should be greater or equal to k.
        size_t k_idx = 0;
        size_t o_idx = 0;
        int k = std::stoi(args[args.size() - 3], &k_idx);
        int o = std::stoi(args[args.size() - 1], &o_idx);
        if (k_idx < std::string(args[args.size() - 3]).length() || k <= 0) {
            std::string errorMsg3 = errorMsg + " - specifically : input k " + args[args.size() - 3] + " is not a valid positive integer.";
            throw std::invalid_argument(errorMsg3);
        } 
        if (o_idx < std::string(args[args.size() - 1]).length() || o <= 0) {
            std::string errorMsg4 = errorMsg + " - specifically : input o " + args[args.size() - 1] + " is not a valid positive integer.";
            throw std::invalid_argument(errorMsg4);
        }
        if (o < k) {
            std::string errorMsg5 = errorMsg + " - specifically : input o " + args[args.size() - 1] + " was smaller than input k " + args[args.size() - 3] + ".";
            throw std::invalid_argument(errorMsg5);
        }

        // check, for input 'args[0] -a p k textfile o', (6 input parameters).
        // : args[1] should be an option (starts with '-'), '-a' is the only allowed option.
        // : args[2] should be a non-negative real number.
        double p = 0.0;
        if (args.size() == 6) {
            if (args[1][0] != '-') { // args is a char* not a string, cannot use .at(index)
                std::string errorMsg6 = errorMsg + " - specifically : " + args[1] + " is an not an option.";
                throw std::invalid_argument(errorMsg6);
            }
            if (args[1] != "-a") {
                std::string errorMsg7 = errorMsg + " - specifically : " + args[1] + " is an unknown option.";
                throw std::invalid_argument(errorMsg7);
            }
            size_t p_idx = 0;
            p = std::stod(args[2], &p_idx);
            if (p_idx < std::string(args[2]).length() || p < 0) {
                std::string errorMsg8 = errorMsg + " - specifically : " + args[2] + " is an not a valid non-negative real number.";
                throw std::invalid_argument(errorMsg8);
            }
        }

        // checkers in main.cpp done
        // 
        // now using classes ModelCreate & ModelTextGenerator to create model and generate new text.

        // creating model.
        ModelCreate model;    // args[args.size() - 2] is the filename.
        model.kgram_initial_maps(args[args.size() - 2], k, errorMsg); // may throw runtime_error : when text length f <= k. updates map_ and map_freq_ and chars_.
        model.kgram_estimates_map(p); // updates map_ and map_standard_estimates

        ModelTextGenerator model_text_generator(model);
        std::string output_text = model_text_generator.text_generator(k, o, p);

        // since the code seemd shorter than the designated output length o, cout the output_text's length.
        std::cout << "Genererated text (längd: " << output_text.length() << "/" << o << "):\n";

        // main.cpp prints the text in the terminal. std::cout
        std::cout << output_text << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
