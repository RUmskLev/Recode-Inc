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



void Country::closeAllRoads(){
        for(int i{0}; i < this->rv.size(); ++i){
                this->closeRoad(i + 1);
        }
}
void Country::closeAllAirRoads(){
        for(int i{0}; i < this->av.size(); ++i){
                this->closeAirRoad(i + 1);
        }
}
void Country::closeAllWaterRoads(){
        for(int i{0}; i < this->wv.size(); ++i){
                this->closeWterRoad(i + 1);
        }
}

void Country::makeAllRoads(){
        for(int i{0}; i < this->rv.size(); ++i){
                if(this->noc != i + 1){
                        this->makeRoad(i + 1);
                }
        }
}
void Country::makeAllAirRoads(){
        for(int i{0}; i < this->av.size(); ++i){
                if(this->noc != i + 1){
                        this->makeAirRoad(i + 1);
                }
        }
}
void Country::makeAllWaterRoads(){
        for(int i{0}; i < this->wv.size(); ++i){
                if(this->noc != i + 1){
                        this->makeWaterRoad(i + 1);
                }
        }
}



//class World
void World::closeCountry(int i)
{
        this->countries[i - 1]->closeAllRoads();
        for(int j{0}; j < this->countries.size(); ++j){
                if(j != i - 1){
                        this->countries[j]->closeRoad(i);
                }
        }
}
void World::closeAirCountry(int i)
{
        this->countries[i - 1]->closeAllAirRoads();
        for(int j{0}; j < this->countries.size(); ++j){
                if(j != i - 1){
                        this->countries[j]->closeAirRoad(i);
                }
        }
}
void World::closeWaterCountry(int i)
{
        this->countries[i - 1]->closeAllWaterRoads();
        for(int j{0}; j < this->countries.size(); ++j){
                if(j != i - 1){
                        this->countries[j]->closeWaterRoad(i);
                }
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

