#include "game_neural_net.hpp"
#include <string>
#include <fstream>
#include <iostream>

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


// std::vector<double> load_target(const std::string& filename) {
//     std::vector<double> target(8, 0);

//     std::vector<std::vector<double>> inputTrainData;
//     inputTrainData = loadFileIntoVector("assets/input.txt");

//     std::vector<std::vector<double>> outputTrainData;
//     outputTrainData = loadFileIntoVector("assets/output1.txt");

//     // поменять отображение вектора input->target по нужной логике
//     double sumFirst18 = 0;
//     for (int i = 0; i < 18; ++i) {
//         sumFirst18 += input[i];
//     }

//     double sumSecond4 = 0;
//     for (int i = 0; i < 4; ++i) {
//         sumSecond4 += input[18 + i];
//     }

//     double sumThird14 = 0;
//     for (int i = 0; i < 14; ++i) {
//         sumThird14 += input[22 + i];
//     }

//     target[0] = sumFirst18 / 18.0;
//     target[1] = sumSecond4 / 4.0;
//     target[2] = sumThird14 / 14.0;
//     target[3] = ((sumFirst18 + sumSecond4 + sumThird14) / 36.0 > 0.5) ? 1.0 : 0.0;
//     target[4] = sumFirst18 > 9 ? 1.0 : 0.0;
//     target[5] = (sumFirst18 + sumSecond4) / 22.0;
//     target[6] = (sumSecond4 + sumThird14) / 18.0;
//     target[7] = (sumFirst18 + sumThird14) / 32.0;
//     // ===============

//     return target;
// }

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