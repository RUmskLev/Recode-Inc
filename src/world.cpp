#include "world.h"


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

int Country::getPopulation()
{
        return this->population;
}
int Country::getInfected()
{
        return this->infected;
}
double Country::getProbVir()
{
        return this->probabilityVirus;
}
double Country::getSpeedVir()
{
        return this->speedVirus;
}
int Country::getNOC()
{
        return this->noc;
}
std::vector<int> Country::getRV()
{
        return this->rv;
}
std::vector<int> Country::getAV()
{
        return this->av;
}
std::vector<int> Country::getWV()
{
        return this->wv;
}
void Country::upInfected(int inf)
{
        this->infected += inf;
}
void Country::updateProbVir(double newProbVir)
{
        this->probabilityVirus = newProbVir;
}
void Country::updateSpeedVir(double newSpeed)
{
        this->speedVirus = newSpeed;
}





//class World
Country* World::getCountry(int i)
{
        return this->countries[i - 1];
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

void World::makeAllRoads(int i)
{
        for(int j{1}; j <= this->countries.size(); ++j){
                if(i != j){
                        this->makeRoad(i, j);
                }
        }
}
void World::makeAllAirRoads(int i)
{
        for(int j{1}; j <= this->countries.size(); ++j){
                if(i != j){
                        this->makeAirRoad(i, j);
                }
        }
}
void World::makeAllWaterRoads(int i)
{
        for(int j{1}; j <= this->countries.size(); ++j){
                if(i != j){
                        this->makeWaterRoad(i, j);
                }
        }
}


void World::closeAllAllCountries()
{
        for(int i{1}; i<= this->countries.size(); ++i){
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
        countries.push_back(&country);
}

void World::initStartWorld()
{       
        this->closeAllAllCountries();

        for(int i{1}; i <= this->countries.size(); ++i){
                Country* country = this->getCountry(i);
                std::cout << country->getInfected();
                this->closeRoad(i, i);
                this->closeAirRoad(i, i);
                this->closeWaterRoad(i, i);
                country->updateProbVir(0.0);
                country->updateSpeedVir(0.0);
                country->upInfected(-(country->getInfected()));
        }
        for(int i{1}; i <= this->countries.size(); ++i){
                this->makeRoad(i, i);
                this->makeAirRoad(i, i);
                this->makeWaterRoad(i, i);
                this->makeAllAirRoads(i);
                this->makeAllWaterRoads(i);
        }
}
