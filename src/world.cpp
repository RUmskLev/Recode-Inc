#include "world.h"



//class Country
Country::Country(int pop, int n, int numb){
        population = pop;
        infected = 0;
        probabilityVirus = 0;
        speedVirus = 0;
        noc = numb;
        for(int i{0}; i < n; ++i){
                av.push_back(0);
                wv.push_back(0);
                rv.push_back(0);
        }
}

void Country::makeRoad(int i)
{
        this->rv[i - 1] = 1;
}
void Country::makeAirRoad(int i)
{
        this->av[i - 1] = 1;
}
void Country::makeWaterRoad(int i)
{
        this->wv[i - 1] = 1;
}


void Country::closeRoad(int i)
{
        this->rv[i - 1] = 0;
}
void Country::closeAirRoad(int i)
{
        this->av[i - 1] = 0;
}
void Country::closeWaterRoad(int i)
{
        this->wv[i - 1] = 0;
}







//class World
World::World(int n)
{
        for(int i{0}; i < 0; ++i){
                countries.push_back(nullptr);
        }
}



void World::makeRoad(int country1, int country2)
{
        this->countries[country1 - 1]->makeRoad(country2);
        this->countries[country2 - 1]->makeRoad(country1);
}
void World::makeAirRoad(int country1, int country2)
{
        this->countries[country1 - 1]->makeAirRoad(country2);
        this->countries[country2 - 1]->makeAirRoad(country1);
}
void World::makeWaterRoad(int country1, int country2)
{
        this->countries[country1 - 1]->makeWaterRoad(country2);
        this->countries[country2 - 1]->makeWaterRoad(country1);
}

void World::closeRoad(int country1, int country2)
{
        this->countries[country1 - 1]->closeRoad(country2);
        this->countries[country2 - 1]->closeRoad(country1);
}
void World::closeAirRoad(int country1, int country2)
{
        this->countries[country1 - 1]->closeAirRoad(country2);
        this->countries[country2 - 1]->closeAirRoad(country1);
}
void World::closeWaterRoad(int country1, int country2)
{
        this->countries[country1 - 1]->closeWaterRoad(country2);
        this->countries[country2 - 1]->closeWaterRoad(country1);
}


void World::closeCountry(int i)
{
        for(int j{1}; j <= this->countries.size(); ++j){
                if(j != i){
                        this->closeRoad(i, j);
                }
        }
}
void World::closeAirCountry(int i)
{
        for(int j{1}; j <= this->countries.size(); ++j){
                if(j != i){
                        this->closeAirRoad(i, j);
                }
        }
}
void World::closeWaterCountry(int i)
{
        for(int j{1}; j <= this->countries.size(); ++j){
                if(j != i){
                        this->closeWaterRoad(i, j);
                }
        }
}

void World::makeAllRoads(int i){
        for(int j{1}; j <= this->countries.size(); ++j){
                if(i != j){
                        this->makeRoad(i, j);
                }
        }
}
void World::makeAllAirRoads(int i){
        for(int j{1}; j <= this->countries.size(); ++j){
                if(i != j){
                        this->makeAirRoad(i, j);
                }
        }
}
void World::makeAllWaterRoads(int i){
        ffor(int j{1}; j <= this->countries.size(); ++j){
                if(i != j){
                        this->makeWaterRoad(i, j);
                }
        }
}


void World::closeAllAllCountries()
{
        for(int i{1}; i<= this-countries.size(); ++i){
                this->closeCountry(i);
                this->closeAirCountry(i);
                this->closeWaterCountry(i);
        }
}


void World::makeAllAllRoads()
{
        for(int i{1}; i <= this->countries.size(); ++i){
                this->makeAllRoads(i);
                this->makeAllAirRoads(i);
                this->makeAllWaterRoads(i);
        }
}

void World::addCountry(Country &country)
{
        countries[country.noc - 1] = &country;
}
