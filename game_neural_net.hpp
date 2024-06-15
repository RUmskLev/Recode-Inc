#include "neural_net.hpp"
/**
*\file game_neural_net.hpp
* 
*This file contains the function to start the Neural Network
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
NeuralNetwork &&game_neural_network(std::vector<double> (*generate_target)(const std::vector<double>&), std::vector<std::vector<double>> &data, std::vector<std::vector<double>> &targets, int overlearn_coefficient = 5,
                                    int epochs = 10000, double learningRate = 0.2, std::vector<int> layer_sizes = {36, 24, 16, 8},
                                    double needed_accuracy = 0.99);