#include "virus.h"
#include "world.h"
#include "neural_net_main.cpp"
#include <random>


void game_space(){
    //

    //
    Virus covid19;
    Country country1(1000000, 5, 1);
    Country country2(5000000, 5, 2);
    Country country3(500000, 5, 3);
    Country country4(3200000, 5, 4);
    Country country5(1500000, 5, 5);
    World world;
    world.addCountry(country1);
    world.addCountry(country2);
    world.addCountry(country3);
    world.addCountry(country4);
    world.addCountry(country5);
    for(int i{1}; i <= 5; ++i){
        world.makeRoad(i, i);
        world.makeAirRoad(i, i);
        world.makeWaterRoad(i, i);
        world.makeAllAirRoads(i);
        world.makeAllWaterRoads(i);
    }
    //

    //
    std::vector<std::vector<double>> data;
    std::vector<std::vector<double>> targets;
    NeuralNetwork nn = game_neural_network(
        generate_target, data, targets,33, 10000,
        0.15, {100, 24, 16, 38}, 0.99);
    std::vector<double> input(100, 0.0);
    input[0] = 5.0;
    std::vector<double> output;
    // Вход
    // 1-количество стран 
    // 25 - аэропорты, 25 - порты, 25 - дороги/жд, итого 75
    // 14 -вирус
    // 10 - популяции и заражённые в стране
    // 100
    // Выход
    // 1 - ставить метку балла или нет
    // 1 - куда ставить (по 0,2 на страну)
    // 10 - вероятности поппадания в страны и скорость вируса
    // 5 - внешнее закрытие аэропортов
    // 5 - внешнее закрытие портов
    // 5 - внутреннее закрытие жд
    // 5 - внутреннее закрытие аэропортов
    // 5 - внутреннее закрытие портов 
    // 1 - скорость лекарства
    // 38
    //
    //
    // Переменная победы или поражения
    int wl = 0;
    // Переменная  замарозки игры
    int freeze = 1;
    //
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist(0, 100000);
    int rand_value{0};
    int rand_of_inf{0};
    //
    while(true){
        if(freeze){
            // create new values
            for(int i{0}; i < 5; ++i){
                Country country{*world.getCountry(i + 1)};
                std::vector<int> rv = country.getRV();
                std::vector<int> av = country.getAV();
                std::vector<int> wv = country.getWV();
                int infected = country.getInfected();
                int population = country.getPopulation();
                input[90 + i * 2] = population;
                input[90 + i * 2 + 1] = infected;
                for(int j{0}; j < 5; ++j){
                    input[1 + i * 5 + j] = rv[j] * static_cast<double>(infected) / population;
                    input[26 + i * 5 + j] = av[j] * static_cast<double>(infected) / population;
                    input[51 + i * 5 + j] = wv[j] * static_cast<double>(infected) / population;
                }
                input[76] = covid19.getMedRes();
                input[77] = covid19.getAirTr();
                input[78] = covid19.getWaterTr();
                input[79] = covid19.getBirdTr();
                input[80] = covid19.getBloodTr();
                input[81] = covid19.getInsectTr();
                input[82] = covid19.getRodentTr();
                input[83] = covid19.getLivestockTr();
                input[84] = covid19.getIntestines();
                input[85] = covid19.getLungs();
                input[86] = covid19.getBlood();
                input[87] = covid19.getSkin();
                input[88] = covid19.getImmune();
                input[89] = covid19.getCns();
            }
            //
            output = nn.feedforward(input);
            if(output[37] == 1.0){
                break;
            }
            //
            // Update values
            for(int i{0}; i < 5; ++i){
                Country country{*world.getCountry(i + 1)};
                country.updateProbVir(output[2 + i * 2]);
                country.updateSpeedVir(output[3 + i * 2]);
                if(output[12 + i] >= 0.5){
                    world.closeAirCountry(i + 1);
                }
                if(output[17 + i] >= 0.5){
                    world.closeWaterCountry(i + 1);
                }
                if(output[22 + i] >= 0.5){
                    world.closeRoad(i + 1, i + 1);
                }
                if(output[27 + i] >= 0.5){
                    world.closeAirRoad(i + 1, i + 1);
                }
                if(output[32 + i] >= 0.5){
                    world.closeWaterRoad(i + 1, i + 1);
                }
            }
            //
            if(output[0] >= 0.5){
                int i{(static_cast<int>(output[1] / 0.2)) % 5};

            }
            //
            int sumInfected{0};
            for(int i{0}; i < 5; ++i){

                int population = world.getCountry(i)->getPopulation();
                int infected = world.getCountry(i)->getInfected();
                int speedVirus = static_cast<int>(world.getCountry(i)->getSpeedVir() * population);
                double probability = world.getCountry(i)->getProbVir();
                std::uniform_int_distribution<int> distInf(0, speedVirus);

                if(infected == 0){

                    rand_value = dist(gen);
                    rand_of_inf = distInf(gen);

                    if(rand_value / 100000.0 <= probability){
                        world.getCountry(i)->upInfected(rand_of_inf);
                    }
                }else if(infected != population){
                    rand_of_inf = distInf(gen);
                    world.getCountry(i)->upInfected(std::min(rand_of_inf, population - infected));
                }
                sumInfected += world.getCountry(i)->getInfected();
            } 
            if(sumInfected == 11200000){
                wl = 1;
                break;
            }
        }
    }
}