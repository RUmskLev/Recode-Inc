#include "game_neural_net.hpp"
#include <vector>

/**
*\file game_neural_net.cpp
* 
*This file contains the functions to start the Neural Network
*/

/**
*This function starts the neural network
*\param[in] data includes all values in Neural Network of type std::vector<double
*\param[in] targets includes all the values of the aim dataset of type std::vector<std::vector<double>
*\param[in] overlearn_coefficient displays the refitting factor of type int
*\param[in] epochs includes the amount of the time Neural Network starts of type int
*\param[in] learningRate includes the speed of the learning of Neural Network of type double
*\param[in] layer_sizes includes the amount of layers
*
*\return pointer to the Neural Network result
 */
NeuralNetwork &&game_neural_network(std::vector<double> (*generate_target)(const std::vector<double>&),
                                    std::vector<std::vector<double>> &data, std::vector<std::vector<double>> &targets,
                                    int overlearn_coefficient, int epochs, double learningRate,
                                    std::vector<int> layer_sizes, double needed_accuracy)
{
    NeuralNetwork *nn = new NeuralNetwork(layer_sizes);
    std::vector<std::vector<double>> train_data, train_targets;
    for (int i = 0; i < (1 << 18); ++i) {
        std::vector<double> input(36, 0);
        for (int j = 0; j < 36; ++j) {
            input[j] = (i & (1 << j)) ? 1 : 0;
        }

        data.push_back(input);
        if (i % overlearn_coefficient == 0) {
            train_data.push_back(input);
        }
    }
    for (int i = 0; i < data.size(); ++i) {
        targets.push_back(generate_target(data[i]));
    }
    for (int i = 0; i < train_data.size(); ++i) {
        train_targets.push_back(generate_target(train_data[i]));
    }
    std::cout << "Training data size: " << train_data.size() << " targets size: " << train_targets.size() << std::endl;
    std::cout << "Data size: " << data.size() << " targets size: " << targets.size() << std::endl;
    nn->train(train_data, train_targets, data, targets, epochs, learningRate, needed_accuracy);
    return std::move(*nn);
}
