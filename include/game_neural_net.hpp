#ifndef GAME_NEURAL_NET_H
#define GAME_NEURAL_NET_H

#include "neural_net.hpp"
#include <vector>

NeuralNetwork &&game_neural_network(std::vector<double> (*generate_target)(const std::vector<double>&), std::vector<std::vector<double>> &data, std::vector<std::vector<double>> &targets, int overlearn_coefficient = 5,
                                    int epochs = 10000, double learningRate = 0.2, std::vector<int> layer_sizes = {36, 24, 16, 8},
                                    double needed_accuracy = 0.99);


// метод для генерации целевого вектора по начальному вектору для создания датасета
std::vector<double> generate_target(const std::vector<double>& input) {
    std::vector<double> target(8, 0);


    // поменять отображение вектора input->target по нужной логике
    double sumFirst18 = 0;
    for (int i = 0; i < 18; ++i) {
        sumFirst18 += input[i];
    }

    double sumSecond4 = 0;
    for (int i = 0; i < 4; ++i) {
        sumSecond4 += input[18 + i];
    }

    double sumThird14 = 0;
    for (int i = 0; i < 14; ++i) {
        sumThird14 += input[22 + i];
    }

    target[0] = sumFirst18 / 18.0;
    target[1] = sumSecond4 / 4.0;
    target[2] = sumThird14 / 14.0;
    target[3] = ((sumFirst18 + sumSecond4 + sumThird14) / 36.0 > 0.5) ? 1.0 : 0.0;
    target[4] = sumFirst18 > 9 ? 1.0 : 0.0;
    target[5] = (sumFirst18 + sumSecond4) / 22.0;
    target[6] = (sumSecond4 + sumThird14) / 18.0;
    target[7] = (sumFirst18 + sumThird14) / 32.0;
    // ===============

    return target;
}


// int main() {
//     std::vector<std::vector<double>> data;
//     std::vector<std::vector<double>> targets;

//     // game_neural_network генерирует всевозможные комбинации исходных данных,
//     // после чего для каждого из них создает целевой вектор и обучает нейросеть
//     // на этих данных.
//     //
//     // game_neural_network(std::vector<double> (*generate_target)(const std::vector<double>&),
//     //      std::vector<std::vector<double>> &data, std::vector<std::vector<double>> &targets,
//     //                          int overlearn_coefficient, int epochs, double learningRate,
//     //                          std::vector<int> layer_sizes, double needed_accuracy)
//     //
//     // generate_target - метод для генерации целевого вектора по начальному вектору для создания датасета
//     // 
//     // data - датасет для обучения, пустой вектор, внутри это вектор векторов со всеми комбинациями
//     // 36 параметров, которые принимают значения 0 или 1.
//     // 
//     // targets - целевые значения для обучения, пустый вектор
//     // 
//     // overlearn_coefficient - коэффициент переобучения, то есть если overlearn_coefficient = 5, то
//     // каждый 5 элемент датасета будет использоваться для обучения нейросети, тем не менее проверка
//     // точности будет проводиться на всём датасете
//     // 
//     // epochs - количество эпох обучения, 10000 по умолчанию, может быть меньше, если необходимая
//     // точность достигнута
//     // 
//     // learningRate - скорость обучения
//     // 
//     // layer_sizes - размеры слоей, 36 - первый слой, 24 - второй, 16 - третий и 8 последний.
//     // 
//     // needed_accuracy - необходимая точность обучения, 0.99 по умолчанию, проверяется на всём датасете
//     //
//     // можно менять параметры, если необходимо
//     //
//     // в текущей конфигурации обучается за ~2200 +- 200 эпох (с данной функцией generate_target)
//     // если target будут значениями 0 и 1, то обучение будет быстрым
//     // 
//     NeuralNetwork nn = game_neural_network(
//         generate_target, data, targets,33, 10000,
//         0.15, {36, 24, 16, 8}, 0.99);

//     nn.print_train_result(data, targets);

//     return 0;
// }

/**
*\file neural_net.cpp
* 
*This file contains encryption and decryption functions of all neural net types and data validation functions
*/

/**
*
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

        // // First 18 parameters divided into triplets
        // for (int j = 0; j < 18; j += 3) {
        //     int triplet = (i >> j) & 0b111;
        //     if ((triplet & 0b001) == 0) {
        //         input[j] = 0;
        //         input[j+1] = 0;
        //         input[j+2] = 0;
        //     } else {
        //         input[j] = 1;
        //         input[j+1] = (triplet & 0b010) >> 1;
        //         input[j+2] = (triplet & 0b100) >> 2;
        //     }
        // }

        // // Next 4 parameters divided into duets
        // for (int j = 18; j < 22; j += 2) {
        //     int duet = (i >> (j-18)) & 0b11;
        //     if ((duet & 0b01) == 0) {
        //         input[j] = 0;
        //         input[j+1] = 0;
        //     } else {
        //         input[j] = 1;
        //         input[j+1] = (duet & 0b10) >> 1;
        //     }
        // }

        // // Remaining 14 parameters divided into duets
        // for (int j = 22; j < 36; j += 2) {
        //     int duet = (i >> (j-18)) & 0b11;
        //     if ((duet & 0b01) == 0) {
        //         input[j] = 0;
        //         input[j+1] = 0;
        //     } else {
        //         input[j] = 1;
        //         input[j+1] = (duet & 0b10) >> 1;
        //     }
        // }

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

    // nn->train(train_data, train_targets, data, targets, epochs, learningRate, needed_accuracy);

    return std::move(*nn);
}


#endif