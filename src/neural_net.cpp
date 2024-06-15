#include "neural_net.hpp"



double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoidDerivative(double x) {
    return x * (1 - x);
}

NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : layer_sizes(layerSizes) {
    initializeWeights();
}

void NeuralNetwork::initializeWeights() { //initializing weights and ofsets
    srand(time(0));
    int num_layers = layer_sizes.size();

    weights.resize(num_layers - 1);
    biases.resize(num_layers - 1);
    layers.resize(num_layers);

    for (int l = 0; l < num_layers - 1; ++l) {
        weights[l].resize(layer_sizes[l], std::vector<double>(layer_sizes[l + 1]));
        biases[l].resize(layer_sizes[l + 1]);

        for (int i = 0; i < layer_sizes[l]; ++i) {
            for (int j = 0; j < layer_sizes[l + 1]; ++j) {
                weights[l][i][j] = ((double)rand() / RAND_MAX);
            }
        }

        for (int j = 0; j < layer_sizes[l + 1]; ++j) {
            biases[l][j] = ((double)rand() / RAND_MAX);
        }
    }
}

std::vector<double> NeuralNetwork::feedforward(const std::vector<double>& inputs) { //direct neural network traversal
    layers[0] = inputs; //The input layer of the neural network is set equal to the input data.

    for (int l = 0; l < layer_sizes.size() - 1; ++l) { //For each layer, starting from the first to the penultimate one, values ​​are calculated for each neuron in the next layer.
        layers[l + 1].resize(layer_sizes[l + 1]);
        for (int j = 0; j < layer_sizes[l + 1]; ++j) {//For each neuron in the next layer, the sum of the weighted inputs from the neurons in the previous layer is calculated using weights and biases.
            layers[l + 1][j] = biases[l][j];
            for (int i = 0; i < layer_sizes[l]; ++i) {
                layers[l + 1][j] += layers[l][i] * weights[l][i][j];
            }
            layers[l + 1][j] = sigmoid(layers[l + 1][j]);//The activation function (sigmoid) is applied to the resulting sum to obtain the final value of the neuron.
        }
    }
    return layers.back();//The function returns the values ​​of the neurons of the last layer (output layer).
}

void NeuralNetwork::backpropagate(const std::vector<double>& inputs, const std::vector<double>& targets, double learningRate) {//backpropagation process in a neural network
    std::vector<double> outputErrors = targets;//The backpropagate function takes inputs, targets, and learningRate, and uses this data to adjust the weights and biases of the neural network to reduce prediction error.
    for (int i = 0; i < targets.size(); ++i) {
        outputErrors[i] -= layers.back()[i];//The output layer errors are calculated by subtracting the predicted values ​​from the target values.
    }

    std::vector<std::vector<double>> deltas(layer_sizes.size());
    deltas.back() = outputErrors;

    for (int l = layer_sizes.size() - 2; l >= 0; --l) {//Error gradients are calculated for each layer of the network, starting from the last and moving to the first layer.
        deltas[l].resize(layer_sizes[l]);
        for (int i = 0; i < layer_sizes[l]; ++i) {
            double error = 0.0;
            for (int j = 0; j < layer_sizes[l + 1]; ++j) {
                error += deltas[l + 1][j] * weights[l][i][j];
            }
            deltas[l][i] = error * sigmoidDerivative(layers[l][i]);
        }

        for (int i = 0; i < layer_sizes[l]; ++i) {//The weights and biases of the neural network are adjusted based on error gradients and input data, taking into account the learning rate.
            for (int j = 0; j < layer_sizes[l + 1]; ++j) {
                weights[l][i][j] += learningRate * deltas[l + 1][j] * layers[l][i];
            }
        }

        for (int j = 0; j < layer_sizes[l + 1]; ++j) {
            biases[l][j] += learningRate * deltas[l + 1][j];
        }
    }
}//updates the neural network parameters based on the difference between the predicted and target values ​​in order to improve the model's prediction quality.

std::vector<double> NeuralNetwork::train(const std::vector<std::vector<double>>& train_data, const std::vector<std::vector<double>>& train_targets,
                                    const std::vector<std::vector<double>>& check_data, const std::vector<std::vector<double>>& check_targets,
                                    int epochs, double learningRate, double needed_accuracy) {//train() function in the NeuralNetwork class.
//mplements training of a neural network using the transmitted training data (train_data and train_targets) over a given number of epochs (epochs) using 
//the backpropagation method and gradient descent with a given learning rate (learningRate).
    double min_error = 3.4e+38;

    for (int epoch = 0; epoch < epochs; ++epoch) {//for each epoch, the network passes the training data through itself (feedforward), calculates predictions and error, then the weights are corrected (backpropagate) taking into account the resulting error.
        double total_error = 0;
        for (size_t i = 0; i < train_data.size(); ++i) {
            std::vector<double> outputs = feedforward(train_data[i]);
            backpropagate(train_data[i], train_targets[i], learningRate);
            for (int j = 0; j < train_targets[i].size(); ++j) {
                total_error += 0.5 * pow(train_targets[i][j] - outputs[j], 2);
            }
        }

        if (epoch % 10 == 9) {//Every 10 epochs a message is displayed with the epoch number and error. Also, every 100 epochs, the program displays the training results (predictions and errors) on the training and testing data, and also calculates and displays accuracy on the testing data.
            std::cout << "Epoch " << epoch + 1 << "/" << epochs << ", Error: " << total_error << std::endl;
        }

        if (total_error < min_error) {
            min_error = total_error;
            best_weights = weights;
        }

        if (epoch % 100 == 99) {

            std::cout << "=============================" << std::endl;
            print_train_result(train_data, train_targets);
            double accuracy = print_train_result(check_data, check_targets);
            std::cout << "Accuracy: " << accuracy << std::endl;
            std::cout << "=============================" << std::endl;
            if (accuracy > needed_accuracy) {//If the accuracy on the test data reaches the required level (needed_accuracy), then training is interrupted.
                break;
            }
        }
    }

    weights = best_weights;//At the end of training, the last layer of the network (layers.back()) containing predictions for the training data is returned, and the best weights (best_weights) among all epochs are stored.
    return layers.back();
}


double NeuralNetwork::print_train_result(const std::vector<std::vector<double>>& data, const std::vector<std::vector<double>>& targets) {//calculates the number of errors in the neural network's predictions for the training data and their target values.

    size_t count = 0;

    for (int i = 0; i < data.size(); ++i) {
        std::vector<double> output = feedforward(data[i]);
        for (int j = 0; j < output.size(); ++j) {
            if (std::abs(output[j] - targets[i][j]) > 0.05) {//Each prediction is compared with the corresponding target value, and if the difference is greater than 0.05, then it is considered an error.
                ++count;
                break;
            }
        }
    }//outputs the number of errors and the total number of data, and then returns the accuracy of neural network predictions as the ratio of correctly classified examples to the total number of examples.

    std::cout << "(Errors / Overall data): (" << count << " / " << data.size() << ")" << std::endl;

    return (data.size() - count) / double(data.size());

}
