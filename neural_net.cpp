#include "neural_net.hpp"
/**
*\file neural_net.cpp
* 
*This file contains encryption and decryption functions of all neural net types and data validation functions
*/

/**
*This function transfroms input data into the range from 0 to 1
*
*\param[in] x players input of type double
*
*\return real number from 0 to 1
*/
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

/**
*This function counts the value of sigmoid derivative in reverse gradient descent for each weight of type double
*
*\param[in] x weight value of type double
*
*\return the value of sigmoid derivative for each weight
 */
double sigmoidDerivative(double x)
{
    return x * (1 - x);
}

/**
*This is the first consructor of the NeuralNetwork class
*
 *\param[in] layerSizes is the amount of the layers in Neural Network of type std::vector<int>
 *\param[in] seed sets the initial value for the beginning of education the Neural Network of type int
 */
NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes, int seed) : layer_sizes(layerSizes)
{
    initializeWeights(seed);
}

/**
*This is the second constructor of the NeuralNetwork class
*\param[in] filename is the name of the file where will be written the counted weights
 */
NeuralNetwork::NeuralNetwork(std::string filename){
    std::ifstream fin(filename);
    std::string line;
    std::vector<double> line_as_vector;
    std::vector<std::vector<double>> new_weights_part;
    best_weights.clear();

    if (!fin.is_open()) {
        std::cout << "File not found\n";
        fin.close();
    }
    else{
        while (std::getline(fin, line)){
            if (line[0] == ';'){
                best_weights.push_back(new_weights_part);
                new_weights_part.clear();
            }
            else{
                std::stringstream ss(line);
                while(ss.good()){
                    std::string new_num;
                    getline(ss, new_num, ',');
                    // std::cout << new_num << " ";
                    try{
                        line_as_vector.push_back(std::stod(new_num));
                    }
                    catch(std::invalid_argument){};
                }
                new_weights_part.push_back(line_as_vector);
                line_as_vector.clear();
            }
        }
    }
}


/**
 * This function initializes the random values for weights, biases and layers
 * 
 * \param[in] seed sets the initial value for the beginning of education the Neural Network of type int
 */
void NeuralNetwork::initializeWeights(int seed)
{
    srand(time(0));
    int num_layers = layer_sizes.size();
    weights.resize(num_layers - 1);
    biases.resize(num_layers - 1);
    layers.resize(num_layers);
    for (int l = 0; l < num_layers - 1; ++l)
    {
        weights[l].resize(layer_sizes[l], std::vector<double>(layer_sizes[l + 1]));
        biases[l].resize(layer_sizes[l + 1]);
        for (int i = 0; i < layer_sizes[l]; ++i){
            for (int j = 0; j < layer_sizes[l + 1]; ++j){
                weights[l][i][j] = ((double)rand() / RAND_MAX);
            }
        }
        for (int j = 0; j < layer_sizes[l + 1]; ++j){
            biases[l][j] = ((double)rand() / RAND_MAX);
        }
    }
}

/**
 * This function provides the direct distribution 
 * 
 *\param[in] inputs denotes the values of neirons in the input layer of type std::vector<double>
 *
 *\return the activation of the output layer the Neural Network
 */
std::vector<double> NeuralNetwork::feedforward(const std::vector<double>& inputs)
{
    layers[0] = inputs;
    for (int l = 0; l < layer_sizes.size() - 1; ++l)
    {
        layers[l + 1].resize(layer_sizes[l + 1]);
        for (int j = 0; j < layer_sizes[l + 1]; ++j){
            layers[l + 1][j] = biases[l][j];
            for (int i = 0; i < layer_sizes[l]; ++i){
                layers[l + 1][j] += layers[l][i] * weights[l][i][j];
            }
            layers[l + 1][j] = sigmoid(layers[l + 1][j]);
        }
    }
    return layers.back();
}

/**
 * This function reckons the reverse gradient descent to reduce the amount of mistakes in education
 * 
 *\param[in] inputs denotes the values of neirons in the input layer of type std::vector<double>
 *\param[in] targets denotes the values of output layer of neirons of type std::vector<double>
 *\param[in] learningRate denotes the speed of education
 *
 */
void NeuralNetwork::backpropagate(const std::vector<double>& inputs, const std::vector<double>& targets, double learningRate)
{
    std::vector<double> outputErrors = targets;
    for (int i = 0; i < targets.size(); ++i){
        outputErrors[i] -= layers.back()[i];
    }
    std::vector<std::vector<double>> deltas(layer_sizes.size());
    deltas.back() = outputErrors;
    for (int l = layer_sizes.size() - 2; l >= 0; --l)
    {
        deltas[l].resize(layer_sizes[l]);
        for (int i = 0; i < layer_sizes[l]; ++i){
            double error = 0.0;
            for (int j = 0; j < layer_sizes[l + 1]; ++j){
                error += deltas[l + 1][j] * weights[l][i][j];
            }
            deltas[l][i] = error * sigmoidDerivative(layers[l][i]);
        }
        for (int i = 0; i < layer_sizes[l]; ++i){
            for (int j = 0; j < layer_sizes[l + 1]; ++j){
                weights[l][i][j] += learningRate * deltas[l + 1][j] * layers[l][i];
            }
        }
        for (int j = 0; j < layer_sizes[l + 1]; ++j){
            biases[l][j] += learningRate * deltas[l + 1][j];
        }
    }
}

/**
 * This function implements training of the Neural network
 * 
 *\param[in] train_data stands the training player's dataset for the Network of type std::vector<std::vector<double>>
 *\param[in] train_targets stands the training output's dataset of type std::vector<std::vector<double>>
 *\param[in] check_data stands the checking player's dataset of type std::vector<std::vector<double>>
 *\param[in] check_targets stands the checking output dataset of type std::vector<std::vector<double>>
 *\param[in] epochs stans the amount of repeating the education for Neural Network of type int
 *\param[in] learningRate denotes the speed of education
 *\param[in] needed_accuracy stands the neccessary value of the precision of the education
 *
 *\return the activation of the output layer the Neural Network
 */
std::vector<double> NeuralNetwork::train(const std::vector<std::vector<double>>& train_data, const std::vector<std::vector<double>>& train_targets,
                                    const std::vector<std::vector<double>>& check_data, const std::vector<std::vector<double>>& check_targets,
                                    int epochs, double learningRate, double needed_accuracy)
{
    double min_error = 3.4e+38;
    for (int epoch = 0; epoch < epochs; ++epoch){
        double total_error = 0;
        for (size_t i = 0; i < train_data.size(); ++i){
            std::vector<double> outputs = feedforward(train_data[i]);
            backpropagate(train_data[i], train_targets[i], learningRate);
            for (int j = 0; j < train_targets[i].size(); ++j){
                total_error += 0.5 * pow(train_targets[i][j] - outputs[j], 2);
            }
        }
        if (epoch % 10 == 9){
            std::cout << "Epoch " << epoch + 1 << "/" << epochs << ", Error: " << total_error << std::endl;
        }
        if (total_error < min_error){
            min_error = total_error;
            best_weights = weights;
        }
        if (epoch % 100 == 99){
            std::cout << "=============================" << std::endl;
            print_train_result(train_data, train_targets);
            double accuracy = print_train_result(check_data, check_targets);
            std::cout << "Accuracy: " << accuracy << std::endl;
            std::cout << "=============================" << std::endl;
            if (accuracy > needed_accuracy){
                break;
            }
        }
    }
    weights = best_weights;

    return layers.back();
    return layers.back();
}

/**
 * This function displays the result of training
 * 
 *\param[in] data stands the amount of all parametres in Neural Network of type std::vector<std::vector<double>>
 *\param[in] targets stands the amount of final parametres in Neural Network of type std::vector<std::vector<double>>
*\return the error of the training
*/
double NeuralNetwork::print_train_result(const std::vector<std::vector<double>>& data, const std::vector<std::vector<double>>& targets)
{
    size_t count = 0;
    for (int i = 0; i < data.size(); ++i) {
        std::vector<double> output = feedforward(data[i]);
        for (int j = 0; j < output.size(); ++j) {
            if (std::abs(output[j] - targets[i][j]) > 0.05)
            {
                ++count;
                break;
            }
        }
    }
    std::cout << "(Errors / Overall data): (" << count << " / " << data.size() << ")" << std::endl;
    return (data.size() - count) / double(data.size());
}
/**
 * This function returns the values of biases
 * 
 *\return biases
 */
std::vector<std::vector<double>> NeuralNetwork::output_biases()
{
        return biases;
}

/**
*This function returns the best counted weights
*\return best weigths counted by network
 */
std::vector<std::vector<std::vector<double>>> NeuralNetwork::output_best_weights(){
    return best_weights;
}

/**
*This is the function of writing into the file the best weights of Neural Network
 */
void NeuralNetwork::print_weights_to_txt(){
    std::ofstream fout("output.txt");
    for(const auto& i : best_weights){
        for(const auto& j : i){
            for (const auto& k : j){
                fout << k << ",";
            }
            fout << "\n";
        }
        fout << ";\n";
    }
    fout.close();
};
