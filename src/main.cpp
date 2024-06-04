#include "virus.h"
#include "world.h"

int main(int argc, char* argv[])
{
    return 0;
}

void game_space(){
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
    while(true){
        
    }
}