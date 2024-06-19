#include "game_neural_net.hpp"

// метод для генерации целевого вектора по начальному вектору для создания датасета
std::vector<double> generate_target(const std::vector<double>& input) {
    std::vector<double> target(38, 0);


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


int main() 
{
    std::vector<std::vector<double>> data;
    std::vector<std::vector<double>> targets;
    NeuralNetwork nn = game_neural_network(
        generate_target, data, targets,33, 10000,
        0.15, {104, 24, 16, 38}, 0.99);

    nn.print_train_result(data, targets);


    // ниже примеры прогона нейронной сети

    std::vector<double> input_parameters = std::vector<double>(106, 0.0);
    
    for (int i = 0; i < 104; ++i) {
        input_parameters[i] = 1.0;
    }

    // feedforward получает на вход вектор с параметрами и возвращает вектор с выходными параметрами

    std::vector<double> output_parameters = nn.feedforward(input_parameters);

    std::cout << "Input parameters: ";
    for (int i = 0; i < input_parameters.size(); ++i) {
        std::cout << input_parameters[i] << " ";
    }
    std::cout << "Output parameters: ";
    for (int i = 0; i < output_parameters.size(); ++i) {
        std::cout << output_parameters[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
