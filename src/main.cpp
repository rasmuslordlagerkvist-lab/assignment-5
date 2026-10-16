#include "ModelCreate.h"
#include "ModelTextGenerator.h"

int main(int argc, char* argv[]) {

    try {
        if (argc != 4) and (argc != 6) {
            throw std::invalid_argument("Incorrect number of arguments.");
            std::cerr << "Usage: " << argv[0] << " -a p k textfile o\n" << 
            "p a real number greater than 0, k a positive integer, o >= k a positive integer." << std::endl;
        }
    }

    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
