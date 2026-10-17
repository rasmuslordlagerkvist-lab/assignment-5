// class ModelTextGenerator

// Private (variables): 
// const ModelCreate& model_;

// Public (functions): 
// text_generator(p, k, o) - implementing the 'algorithm'. In step 3 : use std::random_device, std::mt19937, std::discrete_distribution, distribution() together with [ModelCreate's map_ (estimates) turned into two vector containers of its estimates and its characters (with corresponding order)]

// maybe splitting up ^^ into smaller helper functions. Not sure on this until I actually code it.


class ModelTextGenerator {
    
    private:
        // model object is an instance of the class ModelCreate.
        ModelCreate model;

    public:
        // initialize the class object. (How it is created.)
        ModelTextGenerator(const ModelCreate& input_model);

        // Generates new text
        std::string text_generator(int k, int o, int p);
};
