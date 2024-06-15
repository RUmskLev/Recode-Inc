#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "neural_net.hpp"
#include "doctest.h"

#define epsilon 2

TEST_CASE("Sigmoid"){
    CHECK(sigmoid(0.0) == 0.5);
    CHECK(sigmoid(1.0) == 1/(1+exp(-1)));
}
TEST_CASE("sigmoidDerivative"){
    CHECK(sigmoidDerivative(0.0) == 0.0);
    CHECK(sigmoidDerivative(1.0) == 0.0);
}
TEST_CASE("initializeWeights"){
    NeuralNetwork nn = NeuralNetwork({1,2}, 5);
    std::vector<std::vector<double>> expected_biases = {{0.374004, 0.746147}};
    int expected_biases_i = 0, expected_biases_j = 0;
    for(const auto& i : nn.output_biases()){
        expected_biases_j = 0;
        for(const auto& j : i){
            CHECK(std::abs(j-(expected_biases[expected_biases_i][expected_biases_j]) < epsilon));
            expected_biases_j++;
        }
        expected_biases_i++;
    }
}
TEST_CASE("feedforward"){
    NeuralNetwork nn = NeuralNetwork({20, 23}, 2);
    std::vector<double> expected_feedforward = {0.938918, 0.986961, 0.990221, 0.994744, 0.937937, 0.996735, 0.982522, 0.987243, 0.952651, 0.984878,
    0.793483, 0.988738, 0.982334, 0.983177, 0.922234, 0.997022, 0.988679, 0.96887, 0.943497, 0.972216, 0.989699, 0.986814, 0.910312,};
    int expected_feedforward_i = 0;
    for(const auto& i : nn.feedforward({1, 2, 4})){
        CHECK(std::abs(i - expected_feedforward[expected_feedforward_i]) < epsilon);
        expected_feedforward_i++;
    }
}
TEST_CASE("train"){
    NeuralNetwork nn = NeuralNetwork({10, 2}, 1);
    nn.train({{1}}, {{1}}, {{1}}, {{1}}, 1, 0.3, 0.9999);
    std::vector<std::vector<std::vector<double>>> expected_best_weights =
     {{ {0.0424323,0.563585},
        {0.193304,0.808741},
        {0.604723,0.479873},
        {0.350291,0.895962},
        {0.829272,0.746605},
        {0.174108,0.858943},
        {0.735586,0.513535},
        {0.303995,0.0149846},
        {0.0945663,0.364452},
        {0.147313,0.165899} }};
    nn.print_weights_to_txt();
    int expected_bw_i = 0, expected_bw_j = 0, expected_bw_k = 0;
    for(const auto& i : nn.output_best_weights()){
        expected_bw_j = 0;
        for(const auto& j : i){
            expected_bw_k = 0;
            for(const auto& k : j){
                CHECK(std::abs(k-(expected_best_weights[expected_bw_i][expected_bw_j][expected_bw_k])) < epsilon);
                expected_bw_k++;
            }
            expected_bw_j++;
        }
        expected_bw_i++;
    }
}

TEST_CASE("NeuralNetwork(string filename)"){
    NeuralNetwork nn = NeuralNetwork("test_constructor");
    std::vector<std::vector<std::vector<double>>> constructor_file =
     {{ {0.0424323,0.563585},
        {0.193304,0.808741},
        {0.604723,0.479873},
        {0.350291,0.895962},
        {0.829272,0.746605},
        {0.174108,0.858943},
        {0.735586,0.513535},
        {0.303995,0.0149846},
        {0.0945663,0.364452},
        {0.147313,0.165899} }};
    int expected_cf_i = 0, expected_cf_j = 0, expected_cf_k = 0;
    for(const auto& i : nn.output_best_weights()){
        expected_cf_j = 0;
        for(const auto& j : i){
            expected_cf_k = 0;
            for(const auto& k : j){
                CHECK(std::abs(k-(constructor_file[expected_cf_i][expected_cf_j][expected_cf_k]) < epsilon));
                expected_cf_k++;
            }
            expected_cf_j++;
        }
        expected_cf_i++;
    }
}

TEST_CASE("output_best_weights"){
    NeuralNetwork nn = NeuralNetwork("test_constructor");
    std::vector<std::vector<std::vector<double>>> constructor_file =
     {{ {0.0424323,0.563585},
        {0.193304,0.808741},
        {0.604723,0.479873},
        {0.350291,0.895962},
        {0.829272,0.746605},
        {0.174108,0.858943},
        {0.735586,0.513535},
        {0.303995,0.0149846},
        {0.0945663,0.364452},
        {0.147313,0.165899} }};
    int expected_cf_i = 0, expected_cf_j = 0, expected_cf_k = 0;
    for(const auto& i : nn.output_best_weights()){
        expected_cf_j = 0;
        for(const auto& j : i){
            expected_cf_k = 0;
            for(const auto& k : j){
                CHECK(std::abs(k-(constructor_file[expected_cf_i][expected_cf_j][expected_cf_k]) < epsilon));
                expected_cf_k++;
            }
            expected_cf_j++;
        }
        expected_cf_i++;
    }
}

