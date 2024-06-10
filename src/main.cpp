#include "virus.h"
#include "world.h"
#include <

int main(int argc, char* argv[])
{
    return 0;
}

void game_space(){
    //

    //
    Virus covid19();
    Country country1(1000000, 5, 1);
    Country country2(5000000, 5, 2);
    Country country3(500000, 5, 3);
    Country country4(3200000, 5, 4);
    Country country5(1500000, 5, 5);
    World world(5);
    world.addCountry(country1);
    world.addCountry(country2);
    world.addCountry(country3);
    world.addCountry(country4);
    world.addCountry(country5);
    world.makeAllAllRoads();
    //


    //
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist(0, 100000);
    int rand_value{0};
    int rand_of_inf{0};
    //
    while(true){
        for(int i{0}; i < world.getCountries().size(); ++i){

            int population = world.getCountries()[i]->getPopulation();
            int infected = world.getCountries()[i]->getInfected;
            int speedVirus = (int) (world.getCountries()[i]->getSpeedVir() * population);
            double probability = world.getCountries()[i]->getProbVir();
            std::uniform_int_distribution<int> distInf(0, speedVirus);

            if(infected == 0){

                rand_value = dist(gen);
                rand_of_inf = distInf(gen);

                if(rand_value / 100000.0 <= probability){
                    world.getCountries()[i]->upInfected(rand_of_inf);
                }
            }else if(infected != population){
                rand_of_inf = distInf(gen);
                world.getCountries()[i]->upInfected(rand_of_inf);
            }
        } 
    }
}